local array = require"array"

local a = array.new(10)
local b = array.new(10)

--print(a)

a[2] = true
b[2] = false

print(a)
print(b)

local c = a + b;
local d = a * b;

--print(c[2], d[2]);
print(c)
print(d)
