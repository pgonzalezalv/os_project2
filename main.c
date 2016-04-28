#include <error.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libfractal/fractal.h"
#include "main.h"

struct buffer_node *buffer;

int main(int argc, char *argv[])
{

	int test = 0;

	test = reader(argv[1]);


	// il faut un sémaphore pour multi-threader la fonction reader
	// sem_t sem;
	// sem_init(&sem, 0, MAX_BUFFER_SIZE);

	/* TO DO */

	// sem_destroy(&sem);

	return 0;
}

int reader(const char *fichier) {
	FILE *file = NULL;


	file = fopen(fichier, "r");

	// il faut un sem_post
	if (file != NULL) { // file succesfully opened
		struct fractal *new_fract = NULL;
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
				printf("%s %d %d %lf %lf\n", n, w, h, a, b); // ca marche

				int err = push(&buffer, new_fract); // BUG : buffer not declared
				if (err != 0) {
					printf("pas content\n");
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

int calculator(struct fractal *fract) {

	/* TO DO */

	return 0;
}

int push(struct buffer_node **list, struct fractal *new_fract){
	struct buffer_node *new;
  new = malloc(sizeof(*new));

  if (new == NULL)
    return -1;

  new->fract = new_fract;
  new->next = *list;
	new->previous = NULL;
  *list = new;

	return 0;
}

struct fractal* pop(struct buffer_node **list) {
	// if (list == NULL)
		// return 0;

	struct fractal *fract = NULL;
	struct buffer_node *toRemove = *list;

	fract = (*list)->fract;
	*list = (*list)->next;

	free(toRemove);
	return fract;
}

void free_list(struct buffer_node **list) {
	while(list)
		pop(list);
}
