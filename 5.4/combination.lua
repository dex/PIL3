function combination(arr, m)
	local n = #arr
	local ret = {}
	if m == 0 then
		table.insert(ret, {})
	elseif n >= m then
		-- arrary without first element
		local new_arr = {}
		for i = 2, #arr do
			table.insert(new_arr, arr[i])
		end
		-- combinations that must have the first element
		for _, v in pairs(combination(new_arr, m-1)) do
			local cur_result = {}
			table.insert(cur_result, arr[1])
			for _, e in pairs(v) do
				table.insert(cur_result, e)
			end
			table.insert(ret, cur_result)
		end
		-- combinations that must not have the first element
		for _, v in pairs(combination(new_arr, m)) do
			table.insert(ret, v)
		end
	end
	return ret
end

function combinations(arr) 
	for i = 1, #arr do
		-- print combinations that has i elemetns
		for _, v in pairs(combination(arr, i)) do
			-- print element
			for j, e in pairs(v) do
				if j == #v then
					io.write(e)
				else
					io.write(e .. ",")
				end
			end
			print()
		end
	end
end
