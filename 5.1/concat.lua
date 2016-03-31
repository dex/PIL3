function concat(...)
	local str = ""
	for _, s in pairs{...} do
		str = str .. s
	end
	return str
end
