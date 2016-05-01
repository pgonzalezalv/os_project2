#include <error.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libfractal/fractal.h"
#include "main.h"


//struct buffer_node *buffer;
struct buffer_node *head = NULL;
struct buffer_node *tail = NULL;
int buffer_size = 0;

int main(int argc, char *argv[])
{

	int test = 0;

	printf("Reading : %s\n", argv[1]);
	test = reader(argv[1]);


	// il faut un sémaphore pour multi-threader la fonction reader
	// sem_t sem;
	// sem_init(&sem, 0, MAX_BUFFER_SIZE);

	/* TO DO */

	// sem_destroy(&sem);

	return 0;
}
