# Binary name
BIN=main

# Compiler cmd, optimisations options and linkers
CC=gcc
CFLAGS=-g -Wall -W -DNDEBUG
LDFLAGS=-lpthread -lSDL

#
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
HEADER=$(SRC:.c=.h)

# Test using CUnit installed locally
TEST_EXE=$(CC) -I$(HOME)/local/include
TEST_SRC=test/*.c

# Fractal library archive
LIB_FILES=$(wildcard libfractal/*.a)

all: lib main

# Building *.o
%.o: %.c $(HEADER)
	@echo "this is it $^"
	$(CC) $(LDFLAGS) -c $< $(CFLAGS) -Ilibfractal
## main         : Generate fractal - TODO
main: $(OBJ)
	@echo "building $@"
	$(CC) -o $@ $^ libfractal/libfractal.a $(LDFLAGS) $(CFLAGS)

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

launch:
	./main -d --maxthreads 2 fract_inputs/*.txt fileOut
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
