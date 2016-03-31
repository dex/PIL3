function multiload(...)
	local tbl = {...}
	local len = #tbl
	local idx = 1
	return load(function ()
		while true do
			if idx > len then
				return nil
			end
			local elm = tbl[idx]
			if type(elm) == "string" then
				idx = idx + 1
				return elm
			elseif type(elm) == "function" then
				local val = elm()
				if val ~= nil then
					return val
				else
					idx = idx + 1
				end
			else
				error("neither a string nor a function")
			end
		end
	end)
end
