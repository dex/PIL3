function fromto(n, m)
	return function (s, c) 
		if n > m then
			return nil
		end
		if not c then
			return s.from
		end
		c = c + 1
		if c > s.to then
			return nil
		else
			return c
		end
	end, {from=n, to=m}
end
