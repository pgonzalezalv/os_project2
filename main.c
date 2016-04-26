#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libfractal/fractal.h"
#include "main.h"

int main()
{
	// il faut un sémaphore pour multi-threader la fonction reader
	sem_t sem;
	sem_init(&sem, 0, MAX_BUFFER_SIZE);

	/* TO DO */

	sem_destroy(&sem);

	return 0;
}

int reader(const char *fichier) {
	FILE *file = NULL;

	file = fopen(fichier, "r");

	// il faut un sem_post
	if (file != NULL) {
		char name[65] = {0};
		int width = 0;
		int height = 0;
		double a = 0.0;
		double b = 0.0;
		struct fractal *new_fract = NULL;
		int ansLine = 0;

		ansLine = fscanf(file, "%s %d %d %lf %lf", &name, &width, &height, &a, &b);

		while (ansLine != EOF) {
			sem_wait(&sem); //sem_past doit etre appele a chaque creation d'un thread calculator
			if (ansLine == 5) {
				new_fract = fractal_new(name, width, height, a, b);

				int err = push(&buffer, new_fract);
				if (err != 0) {
					error(err, "push \n");
					exit(1);
				}
			}
	  	ansLine = fscanf(file, "%s %d %d %d %lf %lf", &name, &width, &height, &a, &b);
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

int push(struct buffer_node **listStart, struct fractal *new_fract){
	struct buffer_node *n;
  n = (struct buffer_node *)malloc(sizeof(struct buffer_node));

  if (n==NULL)
    return -1;

  n->current = *new_fract; //pb
  n->next = *listStart; //pb
	n->previous = NULL;
  *list = n; //pb

	return 0;
}

struct fract *pop(struct buffer_node **listEnd) {
	if (list == NULL)
		return 0;

	struct buffer_node *n = *listEnd;
	*listEnd = (*listEnd)->previous;
	*listEnd->next = NULL;
	struct fractal* toPop = n->current;
	free(n);
	return(toPop);
}
