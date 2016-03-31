#!/usr/bin/env lua
function allwords ()
	local line = io.read() -- current line
	local pos = 1
	local words = {}
	-- current position in the line
	return function ()
		-- iterator function
		while line do
			-- repeat while there are lines
			local s, e = string.find(line, "%w+", pos)
			if s then
				-- found a word?
				pos = e + 1
				-- next position is after this word
				local word = string.sub(line, s, e)
				if not words[word] then
					-- mark and return the word
					words[word] = true
					return word
				end
			else
				line = io.read() -- word not found; try next line
				pos = 1
				-- restart from first position
			end
		end
		return nil
		-- no more lines: end of traversal
	end
end
