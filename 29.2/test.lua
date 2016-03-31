local array = require"array"

local a = array.new(100)
local b = array.new(100)

print(a)

a[2] = true
b[2] = false

local c = a + b;
local d = a * b;

print(c[2], d[2]);
