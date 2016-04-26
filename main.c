#include <pthread.h>
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

/**
* Lit un fichier sur l'entrée standard
* @return : renvoit 0 si on arrive à la fin du fichier (les fractales ont
* toutes été créées).
* renvoit 0 si on a atteint la fin du fichier sans erreur, 1 sinon
* Il faut un mutex pour chaque ligne lu
*/
int reader(const *char fichier) {
	FILE* reading = NULL;

	reading = fopen(fichier, "r");

	// il faut un sem_post
	if (reading != NULL) {
		const char name[65];
		int width;
		int height;
		double a;
		double b;
		struct fractal *new_fract = NULL;

		int ans_line = fscanf(fichier, "%s %d %d %f %f", &name, &width, &height, &a, &b);

		while (ans_line != EOF) {
			sem_wait(&sem); //sem_past doit etre appele a chaque creation d'un thread calculator
			if (ans_line == 5) {
				new_fract = fractal_new(name, width, height, a, b);

				int err = push(&buffer, new_fract);
				if (err != 0)
					error(err, "push \n");
			}
	  	ans_line = fscanf(fichier, "%s %d %d %d %f %f", &name, &width, &height, &a, &b);
		}

		fclose(fichier);
	} else {
		printf("Error: file pointer is null");
		exit(1);
	}

}

/*
 */
int calculator(struct fractal *fract)

/*
 * Ajoute un noeud à l'avant du buffer.
 * @arg : prend comme argument un pointeur vers le début
 * d'une liste doublement chainee et une structure fractal.
 * @return : 0 le noeud est ajouté à l'avant de la liste,
 * -1 si une erreur apparait.
 */
int push(buffer_node **listStart, struct fractal *new_fract){
	struct buffer_node *n;
  n = (buffer_node *)malloc(sizeof(buffer_node));
  if (n==NULL)
  {
    return -1;
  }
  n->current = *new_fract;
  n->next = *listStart;
	n->previous = NULL;
  *list = n;
  return 0;
}

/*
 * Enleve un élément à la fin du buffer.
 * @arg : prend comme argument un pointeur vers la fin d'une
 * liste doublement chainee.
 * @return : la structure fractal enlevee du buffer.
 */
struct fract *pop(buffer_node **listEnd) {
	if (list == NULL)
		return 0;

	struct buffer_node *n = *listEnd;
	*listEnd = (*listEnd)->previous;
	*listEnd->next = NULL;
	struct fractal* toPop = n->current;
	free(n);
	return(toPop);
}
