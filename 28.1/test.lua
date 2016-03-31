t = filter({1, 3, 20, -4, 5, 2, 3, 1 , 2, 3}, function (x) return x < 5 end)

print("{" .. table.concat(t, ", ") .. "}")
