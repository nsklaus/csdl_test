LIBS = -lSDL2 -lxml2 -lSDL2_image
PROG = myapp
OBJS = main.o src/core.o src/parse_map.o src/make_map.o

-include config.mak

CFLAGS += -I/opt/local/include -Ilibxml2  -g
LDFLAGS += -L/opt/local/lib 

src/parse_map.o: CPPFLAGS += $(shell pkg-config --cflags libxml-2.0)

all: $(PROG)
$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS) $(LIBS)
clean:
	rm -f $(OBJS) $(PROG)

.PHONY: all clean
