require "item"
local function print(...)    oldprint("inventory", ...)end

local M = {}
local pp = setmetatable({}, {__mode = "k"})

local inventory           = {
    __index = function(self, key)
        
            if key == "weight" then
                local weight = 0
                
                 foreach(pp[self], function(v) if v.isItem then weight = v.weight end end)
                return weight
            else
                return pp[self][key]
            end
    end,

    __tostring = function(self)
        return "inventory"
    end,

     __newindex = function(self, key, value)
             if key ~= "weight" then            
                pp[self][key] = value
             end
     end
}

function inventory:addItem(item)
    table.insert(pp[self], item)
end


local function createInventory(owner)
    local inv = setmetatable({}, inventory)
    pp[inv] = {
        -- owner = owner, 
        items = 
        {
            createHelmetSkin(),
            createHelmetIron(),
            createHelmetBronze(),
            createronSword(),
        },
        current = 1,
        keys = {}}
        
    assert(pp[inv], "wrong ppself")        
    return inv
end

local inv = createInventory()

-- inv:addItem(createItem("axe", "old axe", 23, "axe"))

function inv:show(unit)
    print("inv:show")

    local ch
    
    Screen.showInventory(self)
    while ch ~= "Escape" do
        
        ch = controller:playerMove()
        if ch == "B" then 
            showBodyParts(self, unit.bodyParts)
        elseif ch == direct.up then
            self.current = self.current - 1
            if self.current < 1 then
                self.current = 1
            end 
        elseif ch == direct.down then
            self.current = self.current + 1
            if self.current > #self.items then
                self.current = #self.items
            end
        elseif ch == direct.enter then
            print("inv:show enter")
            self.items[self.current]:wear(unit.bodyParts)
            print("inv:show enter")
        else
            
        end
        Screen.showInventory(self)
    end
end

function showItems(inventory, bodyPart, bodyParts)
    
    local inv = inventory
    local tnil = {}
    local bpItemsTable = {}
    
    local index = {}
    print("showItems items", inv, bodyPart, bodyPart.type, #inv.items)
    for i, item in pairs(inv.items) do
        assert(item, "no item")
        print("item =", item, item.type, item.type.bodyParts, item.type.bodyParts.hend)
        print(((item.type or tnil).bodyParts or tnil)[bodyPart.type], bodyPart.type)
        if ((item.type or tnil).bodyParts or tnil)[bodyPart.type] then
            print("item.type.bodyParts[bodyPart.type]", ((item.type or tnil).bodyParts or tnil)[bodyPart.type])
             local artip= nil
             if not bpItemsTable[item.type.weight] then
                print("not bpItemsTable[",item.type.weight,"]")
                bpItemsTable[item.type.weight] = {}
                print("!")
                table.insert(index, item.type.weight)
                print("!")
             end
            print("item.type.weight", item.type.weight)
            table.insert(bpItemsTable[assert(item.type.weight, "no weight")], item)
            print("bpItemsTable[",item.type.weight,"]",bpItemsTable[item.type.weight][1] )
        end
        
    --     -- error("not realized")
        
    end
    print("showItems items after:")
    
    local i = 1
    local j = 1
    print("________________________________before Screen.showItemsList index[", i ,"]", index[i] )
    Screen.showItemsList(bpItemsTable,  index[i] , j, index )
    print("________________________________after Screen.showItemsList index[", i ,"]", index[i] )
    local ch = controller:playerMove()
    while ch ~= direct.esc do
        print("showItems ch =", ch, direct.esc)
        if ch == direct.up then
            j = j - 1
            if j < 1 then j = 1 end
        elseif ch == direct.down then
            j = j + 1            
            if j > #bpItemsTable[index[i]] then j = #bpItemsTable[index[i]] end 
        elseif ch == direct.left then
            i = i - 1
            j = 1
            if i < 1 then i = 1 end
        elseif ch == direct.right then
            i = i + 1
            j = 1
            if i > #index then i = i - 1 end 
        elseif ch == direct.enter then
            local selected_item = bpItemsTable[index[i]][j]
            print("selected_item", selected_item, bodyPart, bodyPart.wear)
            --bodyPart:wear(selected_item)
            selected_item:wear(bodyParts)
        end

        print("-_________________showitems before Screen.showItemsList" )
        Screen.showItemsList(bpItemsTable, index[i], j, index)
        print("____________________showitems after Screen.showItemsList" )
        ch = controller:playerMove()
    end
    print("ch == esc")
end

function showBodyParts(inventory, bodyParts)
    Screen.showBody(bodyParts)
    local ch = controller:playerMove()
    while ch ~= direct.esc do
        
        if ch == direct.up then 
            bodyParts.innerKeys.current = bodyParts.innerKeys.current - 1
        elseif ch == direct.down then 
            bodyParts.innerKeys.current = bodyParts.innerKeys.current + 1
            if bodyParts.innerKeys.current > bodyParts.innerKeys.count then
                bodyParts.innerKeys.current = bodyParts.innerKeys.count
            end
        elseif ch == direct.enter then 
            showItems(inventory, bodyParts.parts[bodyParts.innerKeys.current], bodyParts)
            print("showBodyParts after showItems" )
        end
--        print("showBodyParts after showItems1", bodyParts.innerKeys.current, bodyParts.innerKeys  )
        if bodyParts.innerKeys.current < 1 then 
        
            bodyParts.innerKeys.current = 1 
        elseif  bodyParts.innerKeys.current > bodyParts.innerKeys.count then
        
            bodyParts.innerKeys.current = bodyParts.innerKeys.count
        end
        
        Screen.showBody(bodyParts)
        ch = controller:playerMove()
        
    end
end

M.createInventory = createInventory

M.inv = inv













-- inventory.items           = {axe = "axe description", 
                                -- hammer = "hammer description"
                                -- }
-- inventory.innerKeys       = {current = 0, count = 2}
-- inventory.keys            = {weight = 0, gold = 0}

-- inventory.weight    = 0
-- inventory.gold      = 0
-- inventory.items     = {}

-- itemTable = {name = "", description = "", weight = 0, type = "" }



-- function inventory:show()
    -- screen:showInventory(inventory)
    -- ch = controller:playerMove()
    
    -- while(ch ~= "Escape") do
        -- if(ch == "DownArrow") then
            -- inventory.innerKeys.current = inventory.innerKeys.current + 1
            -- if(inventory.innerKeys.current > inventory.innerKeys.count-1) then inventory.innerKeys.current = 0 end
            -- screen:showInventory(inventory)
            
        -- elseif ch == "UpArrow" then
            -- inventory.innerKeys.current = inventory.innerKeys.current - 1
            -- if(inventory.innerKeys.current < 0 ) then inventory.innerKeys.current = inventory.innerKeys.count - 1 end
            -- screen:showInventory(inventory)
            
        -- else
        -- end
        -- ch = controller:playerMove()
    -- end
    
-- end

-- function showInventory()
    -- screen:showInventory(inventory.items)
    -- controller:playerMove()
-- end

-- print("chars")
-- while true do
    -- controller:playerMove()
    -- screen:show(chars)
-- end

return M