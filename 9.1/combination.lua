function combination(arr, r, result)
	if r == 0 then
		coroutine.yield(result)
	elseif r <= #arr then
		local arr_new = {}
		local result_new = {}
		for i = 2, #arr do table.insert(arr_new, arr[i]) end
		for i = 1, #result do table.insert(result_new, result[i]) end
		--combination of (arr-1, r)
		combination(arr_new, r, result_new)
		--combination of (arr-1, r-1)
		table.insert(result_new, arr[1])
		combination(arr_new, r-1, result_new)
	end
end

function combination_generator(arr, r)
	return coroutine.wrap(function ()
		return combination(arr, r, {})
	end)
end

function print_result(arr)
	local cnt = #arr
	local s = ""
	for i, v in pairs(arr) do
		s = s .. v
		if i ~= cnt then
			s = s .. ","
		end
	end
	print(s)
end
