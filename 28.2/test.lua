t = split("abc:edf\0ef:aa", ":")

print("{" .. table.concat(t, ", ") .. "}")

