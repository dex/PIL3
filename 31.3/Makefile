CFLAGS = $(shell pkg-config --cflags luajit) -fPIC -shared
LDLIBS = $(shell pkg-config --libs luajit) -lpthread
SRCS = $(shell ls *.c)
PROG = $(SRCS:.c=.so)

.PHONY: all clean

all: $(PROG)

$(PROG): $(SRCS)
	cc $(CFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm $(PROG)

run: $(PROG)
	/usr/bin/env luajit ./test.lua

