CC=gcc
CFLAGS=-Wall -I/usr/include/SDL

AR=ar
ARFLAGS=-r

SRC_FILES=$(wildcard *.c) # search for all .c

OBJ_FILES=$(SRC_FILES:.c=.o) # <name.c> becomes <name>.o

LIB_FILES=libfractal.a

## all      : Generate fractal library
all: $(SRC_FILES) $(LIB_FILES)

# Build archive
$(LIB_FILES): $(OBJ_FILES)
	@echo "building $@"
	$(AR) $(ARFLAGS) $@ $^

# Compile fractal library
*.o:
	@echo "building $@"
	$(CC) -o $@ -o $< $(CFLAGS) $(LDFLAGS)

## clean    : Remove auto-generated files
clean:
	@echo "cleaning"
	rm -f $(OBJ_FILES)

## mrproper : Remove all built files
mrproper: clean
	@echo "hardcore cleaning"
	rm -f $(LIB_FILES)

## help     : Show different make options
.PHONY: help
help: Makefile
	@sed -n 's/^##//p' $<
