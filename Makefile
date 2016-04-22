# Binary name
BIN=main

# Compiler cmd, optimisations options and linkers
CC=gcc #Compiler cmd
CFLAGS=-Wall -Werror
LDFLAGS=-lpthread -lSDL

# Test using CUnit installed locally
TEST_EXE=$(CC) -I$(HOME)/local/include
TEST_SRC=test/*.c

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

## main     : Generate fractal - TODO
main: main.c
	@echo "building $@"
	gcc -Wall -Werror -o $@ $<

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
