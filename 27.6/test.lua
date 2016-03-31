#!/usr/bin/env lua
local mylib = require"mylib"

mylib.foreach({x = 10, y = 20}, print)
mylib.foreach(_G, print)
