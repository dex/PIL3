local lib = require"transliterate"
local t = {a="3", b=false, c="5"}
local s = "abcbbbdabc"

lib.settrans(t)

local t2 = lib.gettrans()
for k, v in pairs(t2) do print(k, v) end

print(lib.transliterate(s))
