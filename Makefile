LIBS = -lSDL2
PROG = myapp
OBJS = main.o core.o

#-include config.mak
CFLAGS += -I/opt/local/include
LDFLAGS += -L/opt/local/lib

all: $(PROG)
$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS) $(LIBS)
clean:
	rm -f $(OBJS) $(PROG)

.PHONY: all clean
