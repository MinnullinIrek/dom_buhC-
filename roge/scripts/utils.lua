
direct={up = "UpArrow", down = "DownArrow", left = "LeftArrow", right = "RightArrow", 
s = "S", a= "A", w="W", d="D", e="E", q="Q", z= "Z", c="C", x="X", i = "I", esc = "Escape", enter = "Enter"}


function foreach(t, f, pairF)
    if pairF == nil then pairF = pairs end
    for k, i in pairF(t) do
        f(i, k)
    end
end

Random = {}
function Random:random(upper)
    return math.random(upper)
end

NameDescription = { name="", description = "", symbol = "?"}
function NameDescription:create()
    return setmetatable({}, self)
end
empty = {}
print = function(mes, color)
    screen:setText(tostring(mes), color or "lightRed")
end

local i = 1
function nextSerial()
    i = i+1
    return i
end

function length(t)
    return #t
end
