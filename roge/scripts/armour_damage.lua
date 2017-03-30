local M = {}
--region *.lua



--damageType      = {
--    crush   = {},
--    cutting = {},
--    slash   = {},
--    fire    = {},
--    acid    = {},
--    cold    = {},
--    light   = {},
--    volume  = {}
--}
local function print(...)    oldprint("armourdamage", ...)end
--for i, k in pairs(damageType)

damageType = {
    name    = "crush",
    value   = 0,
    __metatable = "damageType",
    __tostring = function(dt) return string.format("damage type: %s", dt.name) end
}

damage = {
    --damageTypes     = {},
    __metatable     = "damage",
    __tostring      = function(dmg) return "damage" end,
}

function M.createDamageType(name, value)
    
    return setmetatable({name = name, value = value}, damageType)
end

function M.createDamage()
    return setmetatable({}, damage)
end


--endregion

return M