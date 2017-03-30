ar_dmg = require "armour_damage"

local function print(...)    oldprint("item", ...)end

local pp = setmetatable({}, {__mode = "k"})

local Item = {}

--itemType        = {
--    weapon,
--    armour,
--    bullets,
--    usingItems
--}


--local wpType          = { 
--    handCount   = {1, 2},
--    size        = {"small", "short", "medium", "long", "great"}, 
--    type        = {"sword", axe, hammer, stuff, bow, crossbow, sling, shield}, 
--    missile     = {true, false}, 
--    thrown      = {true, false}, 
--    material    = {wood, iron, bronze, cu, ...},
--    __metatable = "weapon"
--}

local wpType          = { 
    __metatable = "weapon"
}




armourType      = {
    --weight      = cloth/ light/ medium/ heavy/ mantyle/ cloack ,
    --bodyParts   = {head, neck},
    --pair        = true/ false/
    --material    = {wood, iron, bronze, cu, ...},
    __metatable = "armour",
    __tostring = function(self)
        local str = "armour".." "..self.weight.." for: "
         for i in pairs(self.bodyParts) do
             str = str.." "..i
         end
        return str
    end

}




local item = {
__index = function(item, key)
        print("__index", item , key)
        if key == "wear" then

            return 
                function(item, bodyParts)
                    if item.weared then
                        print("bodyPart:UNwear(", item, ") weared ==", item.weared)
                        
                        for name, bool in pairs(item.type.bodyParts) do
                            if bool then
                                bodyParts[name][item.type.weight] = nil
                            end

                        end

                        item.weared = false
                    else
                        print("item:wear(", item, ")")
                        print("type = ", item.type)
                        print("type.weight = ", item.type.weight)
                        
                        
                        for name, bool in pairs(item.type.bodyParts) do
                            print("type.bpart.name = ", name, bool )
                            if bool then
                                local lastWearedItem = bodyParts[name][item.type.weight]
                                if lastWearedItem then
                                    print("\n\n_____________________\nlastWearedItem", lastWearedItem)
                                 lastWearedItem:wear(bodyParts)
                                end        

                                bodyParts[name][item.type.weight] = item

                            end
                        end
                        
                        item.weared = true
                        print("bodyPart:wear(", item, ") weared ==", item.weared )
                        event.send(bodyParts, "wear", item)
                    end
                end
        end
        
        return pp[item][key]
    end,
    
__newindex = function(self, key, value)
        pp[self][key] = value
    end,

__call = function(self)
        assert(pp[self].isactive, "item is not active")
            pp[self](pp[self])
    end,

__tostring = function(self)
    return pp[self].name
end,

__metatable = "item"
}

function createItem(name, description, weight, type)
    local item1 = setmetatable({symbol = '$'}, item)
    pp[item1]   = {name = name, description = description, weight = weight, type = type}
    print("createItem", name, item1, getmetatable(item1), item.__metatable, "ss")
    return item1
end

function createWeapon(name, description, weight, wpType, damage)
    local weapon    = createItem(name, description, weight, wpType)
    weapon.wpType   = wpType
    weapon.damage   = damage
    return weapon
end

function createArmour(name, description, weight, arType, damage)
    
    local armour    = createItem(name, description, weight, arType)    
    armour.damage   = damage
    return armour
end

function createHelmetSkin()
    local arType    = setmetatable({weight = "medium", bodyParts = {head = true}, material = "skin"}, armourType)
    return  createItem("skin helm", "helm from skin", 1, arType)
    
end

function createHelmetIron()
    local arType    = setmetatable({weight = "heavy", bodyParts = {head = true}, material = "iron"}, armourType)
    return createItem("iron helm", "helm from iron", 1, arType)
    

end

function createHelmetBronze()
    local arType    = setmetatable({weight = "heavy", bodyParts = {head = true}, material = "bronze"}, armourType)
    return  createItem("bronze helm", "helm from bronze", 1, arType)
    

end

function createronSword()
    local wpType1    = setmetatable({handCount = 1, weight = "short", type = "sword", bodyParts = {hand = true}, material = "iron"}, wpType)
    

    local dmg = setmetatable({cut = ar_dmg.createDamageType("cut", 3), sting = ar_dmg.createDamageType("sting", 1) }, damage)
    return createWeapon("iron sword", "sword from iron", 1, wpType1, dmg) 
end

return Item