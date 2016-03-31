CFLAGS = $(shell pkg-config --cflags luajit)
LDLIBS = $(shell pkg-config --libs luajit)
SRCS = $(shell ls *.c)
PROG = $(SRCS:.c=)

.PHONY: all clean

all: $(PROG)

clean:
	rm $(PROG)

run: $(PROG)
	./$(PROG) ./test.lua
