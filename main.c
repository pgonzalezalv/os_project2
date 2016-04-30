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

int reader(char *fichier)
{
	printf("begin reader\n");
	FILE *file = NULL;

	printf("Open file\n");
	file = fopen(fichier, "r");

	// il faut un sem_post
	if (file != NULL) { // file succesfully opened
		fractal_t *new_fract = NULL;
		char n[65] = {0};
		int w = 0;
		int h = 0;
		double a = 0.0;
		double b = 0.0;
		char line[500]; // maximal characters per line
		int ans_line = 0;

		while (fgets(line, sizeof(line),file)) {
			//BUG : sem is not declared
			// sem_wait(&sem); //sem_past doit etre appele a chaque creation d'un thread calculator
			if (sscanf(line, "%s %d %d %lf %lf", n, &w, &h, &a, &b) == 5
			&& line[0] != '#') {
				new_fract = fractal_new(n, w, h, a, b);
				int err = enqueue(new_fract); // BUG : buffer not declared
				if (err != 0) {
					fclose(file); // si il y a une erreur,s on arrete la lecture
					printf("Error : push didn't worked correctly\n");
					// error(err, "push \n"); // BUG : too few arguments to `error`
					exit(1);
				}
			}
		}
		fclose(file);
	} else {
		printf("Error: file pointer is null\n"); // del when code is finished
		exit(1);
	}

	return 0;
}

int calculator(fractal_t *fract)
{

	int i = 0;
	int count = 0;
	fractal_t *toCompute = NULL;

	toCompute = dequeue();

	for ( i = 0; i < count; i++) {
		fractal_compute_value(toCompute)
	}

	int fractal_compute_value(fractal_t *f, int x, int y);


	return 0;
}
