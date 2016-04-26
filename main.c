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

		int ans_line = fscanf(fichier, "%s %d %d %f %f", &name, &width, &height, &a, &b);

		while (ans_line != EOF) {
			if (ans_line == 5) {
				struct fractal *new_fract = NULL;
				new_fract = fractal_new(name, width, height, a, b);
			}
			ans_line = fscanf(fichier, "%s %d %d %d %f %f", &name, &width, &height, &a, &b);
		}


		fclose(fichier);
	} else {
		printf("Error: file pointer is null");
		exit(1);
	}

}
