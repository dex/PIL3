CFLAGS = $(shell pkg-config --cflags lua) -shared -fPIC
LDLIBS = $(shell pkg-config --libs lua)
SRC = $(shell ls *.c)
PROG = $(SRC:.c=.so)

all: $(PROG)

$(PROG): $(SRC)
	cc $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(PROG)
