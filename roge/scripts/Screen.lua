local dname = "screen"
-- local foreachTOstr = function(tbl)
    -- local str = "\n"
    -- for i, k in pairs(tbl) do
        -- str = str.." "..tostring(k)
    -- end
    -- return str
-- end

-- print = function (...)
    -- form:setText(foreachTOstr({...}))
-- end



print("asdff")
local function deb(...)
    print("SCREEN ", ...)
end

local set = function(...) screen:SetSymbolToConsole(...) end
local c         = {
    black       = "black"  ,
    grey        = "grey"  ,
    lightGrey   = "lightGrey"  ,
    white       = "white"  ,
    blue        = "blue"  ,
    green       = "green"  ,
    cyan        = "cyan"  ,
    red         = "red"  ,
    purple      = "purple"  ,
    lightBlue   = "lightBlue"  ,
    lightGreen  = "lightGreen"  ,
    lightCyan   = "lightCyan"  ,
    lightRed    = "lightRed"  ,
    lightPurple = "lightPurple"  ,
    orange      = "orange"  ,
    yellow      = "yellow"
}
local selected   = "#"
local unselected = " "

local function showTable(tbl, startX, startY, current)
    local i = 0
    local formatString = "%s%s"
    local sel = ""
    local unselected = unselected
    if current then
        sel = unselected
        formatString = "[%s] %s"
    else
        unselected = ""
    end
    
    for key, val in ipairs(tbl) do 
        if current and current == key then sel = selected else sel = unselected end
        set(startX or 0, i + startY or 0, string.format(formatString, sel, tostring(val)), c.lightCyan, c.black)
        i = i + 1
    end
    
    i = 0
    for key, val in pairs(tbl) do 
        -- set(startX or 0,i + startY or 0, string.format(formatString, sel, tostring("##")), c.lightCyan, c.black)
        if current and current == i+1 then sel = selected else sel = unselected end
        set((startX or 0), i + (startY or 0), string.format(formatString, sel, tostring(key)), 
                                                                            c.lightCyan, c.black)
        set((startX or 0) + 20, i + (startY or 0), tostring(val), c.lightCyan, c.black)
        
        i = i + 1
    end
end

--------------------------
Screen = {messages = {}}

Screen.screen = screen
function Screen.showMap(cells, control, consolHeight, consolWidth, startX, startY)
    print("showMap")
    screen:clear()

    for i, cell in ipairs(cells) do
        local visChar = cell:getVisual()
        screen:SetSymbolToConsole(cell.y - startY,cell.x - startX,  visChar.symbol, 
                                                                    visChar.color, visChar.bkColor )
    end

    screen:SetSymbolToConsole(20, 3, control.time, "white", "black")
    screen:SetSymbolToConsole(20, 4, control.hp.value, "white", "black")
    screen:SetSymbolToConsole(20, 5, control.manna.value, "white", "black")
    print("control.time", control.time)
    
    

    screen:changeBuffer()
end

Screen.showInventory = function(tbl)
    print("Screen.showInventory")
    screen:clear()
    local items = tbl.items
    local sel = nil
    
    
    set(0, 1, "-----------------", c.lightCyan, c.black)
    print("showInventory", #items, tbl.current)
    for i, item in ipairs(items) do
        deb("show inventory cicle", item.weared)
        print("showInventory item ==", item, "item.weared =", item.weared)
        if i == tbl.current then
            sel = selected
        else
            sel = unselected
        end
        local itemColor = c.lightCyan
        if item.weared then itemColor = c.grey end
        set(1, i + 2, string.format("[%s] %s", sel, tostring(item)), itemColor, c.black)
        
        set(20, i + 2, '| ' .. item.description, c.lightCyan, c.black)
    end
    deb("showinventory end")
    screen:changeBuffer()
end

Screen.showTable = function(tbl)
    screen:clear()
    local keys = tbl.keys
    local i = 0
    for key, val in pairs(keys) do
        set(i, 0, string.format("%s [%d]", key, val), c.lightCyan, c.black)
        i = i + 20
    end
    set(0, 1, "----------------------------------------------", c.lightCyan, c.black)

    i = 2
    local k = 1;
    local current 
    for key, val in pairs(tbl) do
         if key ~= "keys" and key ~= "innerKeys" then
             local sel = unselected
             print("tbl.innerKeys.current =", tbl.innerKeys.current, k )
             if tbl.innerKeys.current == k then sel = selected current = key end
             set(0, i,  string.format("[%s] %s", sel, key), c.lightCyan, c.black)
             set(20, i, val.value, c.lightCyan, c.black)
             k = k + 1
             i = i + 1
         end
--        showTable(tbl, 0, 2, tbl.innerKeys.current)
        
        
    end

    screen:changeBuffer()
    return current
end

Screen.showBody = function(tbl)
    screen:clear()
    local i = 1
    
    for num, bodyPart in ipairs(tbl.parts) do
        local sel
        if tbl.innerKeys.current == i then sel = selected else sel = unselected end
        set(0, i + 0, string.format("[%s] %s", sel, tostring(bodyPart)), c.lightCyan, c.black)
        local itemTab = 20
        print("Screen.showBody", bodyPart )
        for tipe, item in pairs(bodyPart) do
        print("Screen.showBody1", item, getmetatable(item))
            if getmetatable(item) == "item" then
            print("Screen.showBody item *********")
                set(itemTab, i + 0, tostring(item), c.lightCyan, c.black)
                itemTab = itemTab + 20
            end
        end

        i = i + 1
    end
    
    screen:changeBuffer()

end

Screen.showItems = function(items)
    

end

function Screen.showItemsList(tbl,  wName, J, weights)
    print("Screen.showItemsList", tbl, wName, J, weights)
    assert(tbl, " Screen.showList empty bpItemsTable")
    screen:clear()
    local x = 0
    
    
    --for weightName, itbl in pairs(tbl) do
    for iw = 1, #weights do
        local weightName = weights[iw]
        local itbl = tbl[weightName]
        print("Screen.showItemsList", weightName)
        set(x, 0, weightName, c.lightCyan, c.black)
        local y = 2
            
        for i, k in ipairs(itbl) do
            local sel = unselected
            if wName == weightName and J == i then sel = selected end 
            local itemColor = c.lightCyan
            if k.weared then itemColor = c.grey end
            set(x, i+y, string.format("[%s] %s", sel, tostring(k)), itemColor, c.black )
        end
        x = x + 20
        
    end

    screen:changeBuffer()
end

local selected = {}
function Screen.showBag(bag, i_item)
    print("Screen.showBag")
    i_item = i_item or 1
    
    
    local ch = nil
    repeat

        screen:clear()
        screen:SetSymbolToConsole(1, 0, "---------------------------------", "white", "black")
        for i, item in ipairs(bag) do
            local chosed = '[ ]'
            local color = "white"
            if i_item == i then
                chosed = '[#]'
            end
            screen:SetSymbolToConsole(1, i, string.format("%s %s", chosed, tostring(item)), color, "black")
        end

        screen:changeBuffer()

        ch = controller:playerMove()

        if ch == direct.up then
            if i_item > 1 then i_item = i_item - 1 end
        elseif ch == direct.down then
            if i_item < #bag then i_item = i_item + 1 end
        elseif ch == direct.enter then
                table.insert(selected, table.remove(bag, i_item))
        end
    until ch == direct.esc 

    return selected
end


oldprint = print
