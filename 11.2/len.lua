local mt = {
	__sub = function (a, b) 
		local result = Set{}
		for k, _ in pairs(a) do
			if not b[k] then
				result[k] = true
			end
		end
		return result
	end,
	__tostring = function(s)
		local t = {}
		for k, _ in pairs(s) do
			table.insert(t, k)
		end
		return '{' .. table.concat(t, ", ") .. "}"
	end,
	__len = function(s)
		local count = 0
		for k, _ in pairs(s) do
			count = cout + 1
		end
		return count
	end
}

function Set(l)
	local set = {}
	for _, v in pairs(l) do
		set[v] = true
	end
	setmetatable(set, mt)
	return set
end

