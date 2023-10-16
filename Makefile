CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -g -I/opt/homebrew/include/
LDFLAGS := -L/opt/homebrew/lib -lSDL2 -lSDL2_image

SRCDIR := src
OBJDIR := src
BINDIR := $(shell pwd)

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE := $(BINDIR)/game

-include config.mak

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
