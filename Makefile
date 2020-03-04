bin = bin
program_name = out
program = $(bin)/$(program_name)

cc = gcc
cflags = -g -c
ldflags = -lmingw32 -lSDL2main -lSDL2

include_dirs = -Ic:/libs/SDL2/include
library_dirs = -Lc:/libs/SDL2/lib

rm = rm

objects := $(patsubst %.c, %.o, $(wildcard *.c))
objects := $(addprefix $(bin)/, $(objects))

$(bin)/%.o: %.c %.h defs.h
	$(cc) $(cflags) $(include_dirs) $< -o $@

$(program): $(objects)
	$(cc) $(objects) $(library_dirs) $(ldflags) -o $(program)

all: $(program)
clean:
	$(rm) -f $(program) $(objects)

.PHONY: all clean
