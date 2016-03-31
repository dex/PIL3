local proxies = {}

-- weak
setmetatable(proxies, {__mode="k"})

local function wrapper(f)
	return function(...)
		args = {...}
		-- convert proxy to original object
		for i = 1, #args do
			args[i] = proxies[args[i]] or args[i]
		end
		return f(unpack(args))
	end
end

local function lookup(t, k)
	local obj = proxies[t] or error("object not found")
	local f = obj[k]
	if type(f) ~= "function" then
		error("now allowed to set " .. tostring(k) .. " of object " .. tostring(t))
	end
	f = wrapper(f)
	rawset(t, k, f)
	return f
end

function proxify(obj)
	local proxy = {}
	proxies[proxy] = obj
	setmetatable(proxy, {
		__index = lookup,
		__newindex = function(t, k, v) 
			error("now allowed to set " .. tostring(k) .. " of object " .. tostring(t))
		end
	})
	return proxy
end
