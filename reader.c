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
	int err = 0;

	fractal_t *new_fract = NULL;
	FILE *input = NULL;
	const char *file_name = (char *) param;

	if (strcmp(file_name, "stdin") == 0) {
		log_info("Reading on standard input. %s", param);
		input = stdin;
	} else {
		log_info("Reading file %s.", file_name);
		input = fopen(file_name, "r");
	}

	check(input, "Failed to open %s.", file_name);

	log_info("Succesfully opened file.");

	char line[SIZE_MAX] = "";
	char *n = (char *) malloc (NAME_LEN * sizeof(char));
	int w = 0;
	int h = 0;
	double a = 0.0;
	double b = 0.0;

	while (fgets(line, SIZE_MAX, input)) {
		if (sscanf(line, "%s %d %d %lf %lf", n, &w, &h, &a, &b) == 5
													 && line[0] != '#') {
			new_fract = fractal_new(n, w, h, a, b);
			check(new_fract, "Failed to mallocate %s.", n);

			sem_wait(&empty);
			pthread_mutex_lock(&mutex_buffer);
			check(!enqueue(new_fract), "erreur avec enqueue/");
			sem_wait(&full);
			pthread_mutex_lock(&mutex_buffer);
		}
	}
	check(fclose(input) != 0, "", (char *) param);
	log_info("Succesfully closed file.");
	print_buffer();

	pthread_mutex_lock(&mutex_closing);
	is_reading--;
	pthread_mutex_unlock(&mutex_closing);

	log_info("Reader ends for an input");


	return NULL;

	error:
		fclose(input);
		exit(EXIT_FAILURE);
}
