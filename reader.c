#include <assert.h>
#include <error.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "calculator.h"
#include "dbg.h"
#include "fractal.h"
#include "fractal_buffer.h"
#include "main.h"
#include "reader.h"

void *reader(void *param)
{
	log_info("Reader starts for a param.");
	int err = 0;

	fractal_t *new_fract = NULL;
	FILE *input = NULL;
	const char* file_name = (char *) param;
	char line[SIZE_MAX] = "";

	if (strcmp(file_name, "stdin") == 0) {
		log_info("Reading on standard input.");
		input = stdin;
	} else {
		log_info("Reading param.");
		input = fopen(param, "r");
	}
	// il faut un sem_post
	check(input, "Failed to open %s.", file_name);
	if (input != NULL) { // input succesfully opened
		char n[65] = {0};
		int w = 0;
		int h = 0;
		double a = 0.0;
		double b = 0.0;

		while (fgets(line, sizeof(line),input)) {
			//BUG : sem is not declared
			// sem_wait(&sem); //sem_past doit etre appele a chaque creation d'un thread calculator
			if (sscanf(line, "%s %d %d %lf %lf", n, &w, &h, &a, &b) == 5
			&& line[0] != '#') {
				new_fract = fractal_new(n, w, h, a, b);
				check(new_fract, "Failed to mallocate %s", n);

				sem_wait(&empty);
				pthread_mutex_lock(&mutex_reader);

				err = enqueue(new_fract); // BUG : buffer not declared
				check(err, "erreur avec enqueue, err == %d.", err);
				if (err != 0) {
					fclose(input); // si il y a une erreur,s on arrete la lecture

					pthread_mutex_lock(&mutex_reader);
					count_inputs--;
					pthread_mutex_unlock(&mutex_reader);

					// printf("Error : push didn't worked correctly\n");
					// error(err, "push \n"); // BUG : too few arguments to `error`
					exit(1);
				}

				pthread_mutex_unlock(&mutex_reader);
				sem_post(&full);
			}
		}
		fclose(input);

		pthread_mutex_lock(&mutex_reader);
		count_inputs--;
		pthread_mutex_unlock(&mutex_reader);

		log_info("Reader ends for an input");
	} else {
		printf("Error: input pointer is null\n"); // del when code is finished
		exit(1);
	}

	pthread_exit(NULL);

	error:
    	if(err) fclose(input);
    	if(input) fclose(input);
    	exit(EXIT_FAILURE);
}
