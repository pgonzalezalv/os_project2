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
	char line[SIZE_MAX] = "";
	if (strcmp(file_name, "stdin") == 0) {
		log_info("Reading on standard input. %s", param);
		input = stdin;
	} else {
		log_info("Reading file %s.", file_name);
		input = fopen(file_name, "r");
	}
	check(input, "Failed to open %s.", file_name);
	if (input != NULL) { // input succesfully opened
		log_info("Succesfully opened file.");
		char n[65] = {0};
		int w = 0;
		int h = 0;
		double a = 0.0;
		double b = 0.0;

		while (fgets(line, sizeof(line),input)) {
			// sem_wait(&sem); //sem_past doit etre appele a chaque creation d'un thread calculator
			if (sscanf(line, "%s %d %d %lf %lf", n, &w, &h, &a, &b) == 5
					&& line[0] != '#') {
				new_fract = fractal_new(n, w, h, a, b);
				// print_fractal(new_fract);
				check(new_fract, "Failed to mallocate %s.", n);

				check(!enqueue(new_fract), "erreur avec enqueue/");
			}
		}
		check(fclose(input) != 0, "", (char *) param);
		log_info("Succesfully closed file.");
		print_buffer();

		is_reading--;

		log_info("Reader ends for an input");
	} else {
		exit(EXIT_FAILURE);
	}

	return NULL;

	error:
    	if(err) fclose(input);
    	if(input) fclose(input);
    	exit(EXIT_FAILURE);
}
