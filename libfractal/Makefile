BIN=fractal #Binary name
CC=gcc #Compiler cmd
CFLAGS=-Wall -Werror #Optimisation options
LDFLAGS=-lpthreads -lSDL #Linker
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

.PHONY: clean all

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(OBJ)
