local M = {}local pp = {}function M.createTime1()    local innerTime = {y = {value = 0}, m = {value = 0}, w = {value = 0}, d = {value = 0}, h = {value = 0}, min = {value = 0}, s = {value = 0}, ms = {value = 0}}    Time = setmetatable({},{__index = function(self, key)            if(key == "value") then                    return  string.format("%4.4dy %2.2dm %2.2dd %2.2d:%2.2d:%2.2d",                     innerTime.y.value, innerTime.m.value, innerTime.d.value, innerTime.h.value,                     innerTime.min.value, innerTime.s.value)        else            return  innerTime[key].value        end            end,     -- __newindex = function(self, key, value)        -- innerTime[key].value = value    -- end})    })    function Time:increase(val)        innerTime.s.value = innerTime.s.value + val        print(val)                if(innerTime.s.value > 60) then            local s=innerTime.s.value            innerTime.s.value = math.fmod(s/60)            s = s - innerTime.s.value            innerTime.min.value = math.floor(s/60)        end    end    return Timeendfunction M.createTime()    local innerTime = {value = 0}    Time = setmetatable({}, {__index = function(self,key)        if(key == "value") then                    return screen:valueToTime(innerTime.value)        else            return  innerTime[key]        end    end        })    function Time:increase(value)        innerTime.value = innerTime.value + value    end        return Timeendreturn M