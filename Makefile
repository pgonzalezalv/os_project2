# Binary name
BIN=main

# Compiler cmd, optimisations options and linkers
CC=gcc
CFLAGS=-g -Wall -W -I/usr/include/SDL -Ilibfractal
LDFLAGS=-lpthread -lSDL

#
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

# Test using CUnit installed locally
TEST_EXE=$(CC) -I$(HOME)/local/include
TEST_SRC=test/*.c

# Fractal library archive
LIB_FILES=$(wildcard libfractal/*.a)

all: main

## main         : Generate fractal - TODO
main: $(LIB_FILES) $(OBJ)
	@echo "building $@"
	$(CC) -o $@ -c $< $(LIB_FILES) $(CFLAGS) $(LDFLAGS)

# Building *.o
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

## lib          : Compile libfractal - code DONE, linker -lSDL DONE
lib:
	(cd libfractal; make)
## test         : Compile and execute tests - TODO : multiple tests

## clean_lib    : Remove auto-generated files
clean_lib:
	(cd libfractal; make clean)
## clean        : Remove auto-generated files
clean: clean_lib
	@echo "cleaning"
	rm -f *.o

## mrproper_lib : Remove all built files in libfractal
mrproper_lib:
	(cd libfractal; make mrproper)

## mrproper     : Remove all built files
mrproper: clean mrproper_lib
	@echo "mrproper cleaning"
	rm -f main

## help         : Show different make options
help: Makefile
	@sed -n 's/^##//p' $<
