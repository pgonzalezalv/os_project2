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
struct buffer_node *startB = NULL;
struct buffer_node *endB = NULL;

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
		struct fractal *new_fract = NULL;									//QUESTION : on le met pas sur malloc ??
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
					fclose(file); // si il y a une erreur, on arrete la lecture
					printf("Erreur : push didn't worked correctly\n");
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

//int enqueue(struct buffer_node **list, struct fractal *new_fract){
int enqueue(struct fractal *new_fract){
	struct buffer_node *new;
  new = malloc(sizeof(*new));												//QUESTION : ça suffit pour dire la taille ??

  if (new == NULL) // malloc test
    return -1;

  new->fract = new_fract;
  //new->next = *list;
	new->next = *startB;
	new->previous = NULL;
  //*list = new;
	*startB = new;
	if(startB->next == NULL) //Si le buffer etait vide jusque la
		endB = startB;

	return 0;
}

//struct fractal* dequeue(struct buffer_node **listEnd) {  //QUESTION : j'ai mis listEnd pour bien specifier qu'on partira de la fin du buffer
struct fractal* dequeue() {
	//if (listEnd == NULL){
	if (endB == NULL){
		printf("Error : buffer is empty\n");
		return NULL;
	}

	if (endB == startB) //Si le buffer ne comporte qu'un element
		startB = NULL

	struct fractal *fract = NULL;
	struct buffer_node *toRemove = *listEnd;

	fract = (*listEnd)->fract;
	//free((*listEnd)->fract);
	*listEnd = (*listEnd)->previous;

	free(toRemove);
	return fract;
}
