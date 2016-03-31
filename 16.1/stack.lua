Stack = {}
Stack.__index = Stack

function Stack:isempty()
	return self.head < self.tail
end

function Stack:push(o)
	self.head = self.head + 1
	self.stack[self.head] = o
end

function Stack:top()
	return self.stack[self.head]
end

function Stack:pop()
	if self:isempty() then return nil end
	local o = self:top()
	self.head = self.head - 1
	return o
end

function Stack:new()
	local s = {stack = {}, head = -1, tail = 0}
	setmetatable(s, self)
	return s
end
