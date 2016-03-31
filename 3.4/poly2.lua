function cal_poly2(t, x)
	if type(t) ~= "table" then
		print("please specify table in 1st arg")
		return
	end
	local val = 0
	for i = #t, 1, -1 do
		val = val * x + t[i]
	end
	return val
end
