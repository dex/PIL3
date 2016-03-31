local count = 0
callbacks = {
    StartElement = function (parser, tagname, t, order)
        io.write("+ ", string.rep("  ", count), tagname, " ")
        --for k, v in pairs(t) do io.write(string.format("%s=\"%s\" ", k, v)) end
        for _, k in ipairs(order) do io.write(string.format("%s=\"%s\" ", k, t[k])) end
        io.write("\n")
        count = count + 1
    end,
    EndElement = function (parser, tagname)
        count = count - 1
        io.write("- ", string.rep("  ", count), tagname, "\n")
    end,
}

local lxp = require"lxp"

p = lxp.new(callbacks)
assert(p:parse("<to b='1' dex='6' a='2'><yes c='3'/></to>\n"))
assert(p:parse())
p:close()
