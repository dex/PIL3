function fromto(n, m, step)
	return function (s, c) 
		-- check state
		if s.to > s.from and s.step < 0 then
			return nil
		elseif s.to < s.from and s.step > 0 then
			return nil
		end
		-- generator
		if not c then
			return s.from
		end
		c = c + s.step
		if s.step > 0 and c > s.to then
			return nil
		elseif s.step < 0 and c < s.to then
			return nil
		else
			return c
		end
	end, {from=n, to=m, step=step or 1}
end
