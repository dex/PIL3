require"lproc"
lproc.start("print(lproc.receive(\"ch\"))")

local ret
local i=1
repeat
    print("try " .. i .. " round")
    ret = lproc.send("ch", 1, 2, 3)
    i = i+1
until ret

lproc.exit()
