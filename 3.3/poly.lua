function cal_poly(t, x)
	if type(t) ~= "table" then
		print("please specify table in 1st arg")
		return
	end
	local val = 0
	for i = 1, #t do
		val = val + t[i] * (x ^ (i-1))
	end
	return val
end
