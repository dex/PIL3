function loadwithprefix(prefix, str)
	local is_first = true
	local is_done = false
	return load(function () 
		if is_first then
			is_first = false
			return prefix
		end
		if type(str) == "string" then
			if not is_done then
				is_done = true
				return str
			else
				return nil
			end
		elseif type(str) == "function" then
			return str()
		else
			error("Neither a string nor reader function")
		end
	end)
end
