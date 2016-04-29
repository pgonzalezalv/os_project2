# Binary name
BIN=main

# Compiler cmd, optimisations options and linkers
CC=gcc
CFLAGS=-Wall -W -I/
LDFLAGS=-lpthread -lSDL

# Test using CUnit installed locally
TEST_EXE=$(CC) -I$(HOME)/local/include
TEST_SRC=test/*.c

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

LIB_FILES=$(wildcard libfractal/*.a)

## main     : Generate fractal - TODO
main: $(SRC)
	@echo "building $@"
	gcc -o $@ -c $< $(LIB_FILES) $(CFLAGS) $(LDFLAGS)

## lib      : Compile libfractal - code DONE, TODO : linker -lSDL
## test     : Compile and execute tests - TODO : multiple tests
## clean    : Remove auto-generated files
clean:
	@echo "cleaning"
	rm -f *.o

## mrproper : Remove all built files
.PHONY: clean
mrproper: clean
	@echo "mrproper cleaning"
	rm -f main

## help     : Show different make options
.PHONY: help
help: Makefile
	@sed -n 's/^##//p' $<
