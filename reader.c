#include <assert.h>
#include <error.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "calculator.h"
#include "fractal.h"
#include "fractal_buffer.h"
#include "main.h"
#include "reader.h"

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
				sem_wait(&empty);
				pthread_mutex_lock(&mutex_reader);
				int err = enqueue(new_fract); // BUG : buffer not declared
				if (err != 0) {
					fclose(file); // si il y a une erreur,s on arrete la lecture

					pthread_mutex_lock(&mutex_countf);
					count_files--;
					pthread_mutex_unlock(&mutex_countf);

					printf("Error : push didn't worked correctly\n");
					// error(err, "push \n"); // BUG : too few arguments to `error`
					exit(1);
				}
				pthread_mutex_unlock(&mutex_reader);
				sem_post(&full);
			}
		}
		fclose(file);

		pthread_mutex_lock(&mutex_countf);
		count_files--;
		pthread_mutex_unlock(&mutex_countf);

	} else {
		printf("Error: file pointer is null\n"); // del when code is finished
		exit(1);
	}

	pthread_exit(NULL);
	return 0;
}
