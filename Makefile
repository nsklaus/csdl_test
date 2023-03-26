CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -g -I/opt/homebrew/include/SDL2
LDFLAGS := -L/opt/homebrew/lib -lSDL2 -lSDL2_image

SRCDIR := src
OBJDIR := obj
BINDIR := bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE := $(BINDIR)/game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
