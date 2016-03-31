function stringrep(n)
	local first = true
	return load(function ()
		if first then
			first = false
			print("first")
			return "local r = ''; local args = {...}; local s = args[1];"
		else
			print(n)
			if n < 1 then
				return nil
			elseif n == 1 then
				n = math.floor(n/2)
				return "r = r .. s; return r;"
			else
				if n % 2 == 1 then
					n = math.floor(n/2)
					return "r = r .. s ; s = s .. s;"
				else
					n = math.floor(n/2)
					return "s = s .. s;"
				end
			end
		end
	end)
end
