Chars =  require "chars"
oldprint = print

function print(...) oldprint("unit ", ...) end

local bodyPart = {    
    __tostring = function(self) return self.type.." "..self.name end,    

    wear = function(self, item)
        print("bodyPart:wear(", item, ")")
        print("type = ", item.type)
        self[item.type] = item
        item.weared = true
        print("bodyPart:wear(", item, ") weared ==", item.weared)
    end
}
bodyPart.__index = bodyPart
local M ={}


local whallReplics = {"do not", "no no no", current = 1}

local Filler = {}
--setmetatable(Filler, NameDescription)

M.player = {symbol = "@", color = "cyan"}
setmetatable(M.player, Filler)
function M.player:interaction(filler)
    --print("interaction")
    if(filler.type == "whall") then
        print(whallReplics[whallReplics.current])
        whallReplics.current = 3 - whallReplics.current 
    else
        if filler.characs.finalChar.hp.value <= 0 then
            print("enemy dead")
        else
            print("attack enemy")
        end
        
        local damage = self.characs.damage
        print("damage =", damage.crush)
        for nm, dmg in pairs(damage) do
            print("dmg =")
            --print("dmg =", dmg)
            --filler.characs.finalChar.hp = filler.characs.finalChar.hp - dmg.value
        end
        print("damage end")
        if filler.characs.finalChar.hp.value <= 0 then
            unitDead(filler)
        end
    end
end

function unitDead(unit)
    print("enemy dead")
    local cell = unit.mover.cell
    cell.filler = nil
    if unit.bag then
        cell.bag = unit.bag
    end
end

function M.createBodyParts(lunit)
    assert(lunit)
    local bodyParts         = {
        parts               = {
            setmetatable({type = "head",         name = "",         unit = lunit}, bodyPart), 
            setmetatable({type = "neck",         name = "",         unit = lunit}, bodyPart),  
            setmetatable({type = "shoulder",     name = "left",     unit = lunit}, bodyPart),  
            setmetatable({type = "shoulder",     name = "right",    unit = lunit}, bodyPart), 
            setmetatable({type = "foreram",      name = "left",     unit = lunit}, bodyPart), 
            setmetatable({type = "foreram",      name = "right",    unit = lunit}, bodyPart), 
            setmetatable({type = "arm",          name = "left",     unit = lunit}, bodyPart), 
            setmetatable({type = "arm",          name = "right",    unit = lunit}, bodyPart), 
            setmetatable({type = "hand",         name = "left",     unit = lunit}, bodyPart), 
            setmetatable({type = "hand",         name = "right",    unit = lunit}, bodyPart), 
            setmetatable({type = "chest",        name = "",         unit = lunit}, bodyPart), 
            setmetatable({type = "back",         name = "",         unit = lunit}, bodyPart), 
            setmetatable({type = "belt",         name = "",         unit = lunit}, bodyPart), 
            setmetatable({type = "hip",          name = "left",     unit = lunit}, bodyPart), 
            setmetatable({type = "hip",          name = "right",    unit = lunit}, bodyPart), 
            setmetatable({type = "leg",          name = "left",     unit = lunit}, bodyPart), 
            setmetatable({type = "leg",          name = "right",    unit = lunit}, bodyPart), 
            setmetatable({type = "foot",         name = "left",     unit = lunit}, bodyPart), 
            setmetatable({type = "foot",         name = "right",    unit = lunit}, bodyPart), 
        },
        innerKeys           = {
            current         = 1,
            count           = 19, 
       }, 
        keys                = {}
    }

    for i, part in ipairs(bodyParts.parts) do
        bodyParts[part.type] = part
    end


    bodyParts.unit = lunit
    return bodyParts
end

function M.createFiller(symbol, color, unitType)
    if unitType == "enemy" then
        local enemy = setmetatable({["symbol"] = symbol, ["color"] = color, type = unitType}, Filler)
        enemy.characs = Chars.CreateCharacs()
        enemy.mover = {}
        return enemy
    else
        return setmetatable({["symbol"] = symbol, ["color"] = color, type = unitType}, Filler)
    end
end




return M