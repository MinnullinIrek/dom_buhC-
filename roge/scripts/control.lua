old_require = require

require = function(s)
    return old_require("scripts/"..s)
end

require "strict"
require "Screen"

Map = require "map"
T = require "time"
mp = require "mp"


consolWidth     = 10
consolHeight    = 10
Time = T.createTime()
characs = Chars.characs
control = {time = 0, hp = 1, mn = 0}
--screen
--print = function (...) screen:print(...) end
print("1", "2", 3, 4, 5)
-- Map:createMap(10, 10, "black")
Map:createMapFromTable(mp)
Map.mover.filler.characs = characs

local lunit = Map.mover.filler
lunit.bodyParts         = unit.createBodyParts(lunit)

event.subscribe(lunit.bodyParts, "wear", 
    function(item) 
        print("_______________WEAR EVENT", characs.damage, item.damage)
        for name, dmgType in pairs(item.damage or tnil) do
            print("         WEAR EVENT", characs.damage[name])
            characs.damage[name].value = characs.damage[name].value  + dmgType.value
        end    
    end
)




lunit.inventory         = inventory.inv
--lunit.inventory.unit    = lunit
-- print("start")
local lastCell


local function createCells(map, currentCell)
    local cells         = {}
    -- screen:print("createCells"..mover.cell.x..":"..mover.cell.y)
    local visibleRadius = map.mover.filler.characs.resultChars.visibleRadius

    local curx          = currentCell.x
    local cury          = currentCell.y
    -- screen:print("createCells"..mover.cell.x..":"..mover.cell.y)
    -- screen:print("createCells"..curx..":"..cury)

    local startX = curx - math.floor(consolWidth/2)
    if startX <= 0 then startX = 1 end
    local startY = cury - math.floor(consolHeight/2)
    if startY <= 0 then startY = 1 end

    local endX = curx + consolWidth
    if endX > map.width then endX = map.width end
    if endX - startX > consolWidth  then endX = startX + consolWidth end
    local endY = cury + consolHeight
    if endY > map.height then endY = map.height end
    if endY - startY > consolHeight  then endY = startY + consolHeight end
    -- screen:print(curx.."-"..math.floor(consolWidth/2)..":"..startX)
    -- screen:print(cury.."-"..math.floor(consolHeight/2)..":"..startY)
    for i = 1, endX - startX do
        for j = 1, endY - startY do
            -- screen:print("cell"..(i+startX-1)..":"..(j+startY-1))
            -- print(map.cells[i+startX-1][j+startY-1])
            local c = map.cells[i+startX-1][j+startY-1]
            local d = Map.getDistance(c, currentCell)
            if d < visibleRadius.value then 

                c.visible = Map:isCellVisibleFrom(currentCell, c)
                c.known = c.known or c.visible
            end
            cells[(i-1)*(endY - startY) +j] = c

        end
    end

    return cells, startX, startY
end


function showMap(map)
    control.time = Time.value
    if lastCell then 
        local cells = createCells(map, lastCell)
        foreach(cells, function(cell) cell.visible = false end)
        lastCell = map.mover.cell
    end
    local cells,startX, startY = createCells(map, map.mover.cell)
    Screen.showMap(cells,control, consolHeight, consolWidth, startX, startY)
end


event.subscribe(Map.mover.filler, "move", function(value) Time:increase(value*characs.resultChars.stepTmp) end)

--co =coroutine.create(function()
local function print(...)    oldprint("control", ...)end

function start(args)
print("start")

    while true do
        showMap(Map)
        print("showMap")
        local ch = controller:playerMove()
        print("ch=", ch)
        if ch == direct.c then
            characs:show()
        elseif ch == direct.i then
            print("ch=", "inventory")
            lunit.inventory:show(lunit)
        elseif ch == direct.pickUp then
            print("PickUP")
        else
            Map.mover:Move(ch)
        end
    end
end

print(xpcall(start, debug.traceback))

--end)coroutine.resume(co)


screen:SetSymbolToConsole(1,1,"ddddd", "white", "red")



--[===[require "inventory"
require "chars"

control = { tempus=0, exp=0, innerKeys = {current=0, count=0}}

function plusTemp(dt)
    control.tempus = control.tempus + dt * characs.resultChars.stepTmp
end

function control:show()
    for k,v in pairs(chars) do
        if type(v) ~="table" and type(v) ~="function" then
            self[k] = v
        end
    end
    screen:show(self)
end
control:show()

function print(text)
    screen:print(text)
end
 -- print("ssss")
while true do
    control:show()
    ch= controller:playerMove()
    if(ch == nil)then
    print(ch)
    end
    -- f:write(ch)
    -- f:write("\n")

    if(ch == "I") then
        inventory:show()

    elseif( ch == "C") then
        characs:show()
    else
    end

end




-- io.close(f)

]===]