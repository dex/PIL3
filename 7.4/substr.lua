function substr (str)
	local len = #str
	local from = 1
	local to = 0
	return function ()
		-- iterator function
		to = to+1
		if to > len then
			from = from+1
			to = from
		end
		if from > len then return nil end
		return string.sub(str, from, to)
	end
end
