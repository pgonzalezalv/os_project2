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
#include "dbg.h"
#include "libfractal/fractal.h"
#include "fractal_buffer.h"
#include "main.h"
#include "reader.h"

void *calculator(void *param)
{
	fractal_t *tmp = NULL;

	int *arg = (int *) param;

	while (is_reading != 0) {
		tmp = NULL;

		sem_wait(&full);
		pthread_mutex_lock(&mutex_buffer);
		tmp = dequeue();
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&empty);

		check(!tmp, "erreur avec dequeue.");

		int x = 0;
		int y = 0;
		int width = fractal_get_width(tmp);;
		int height = fractal_get_height(tmp);
		int value = 0;

		double average = 0;
		double total = width * height;

		log_info("Start calcul de fractales");
		for ( y = 0; y < height ; y++) {
			for( x = 0; x < width ; x++)  {
				value = fractal_compute_value(tmp, x, y);
				average += value;
			}
			log_info("Vous etes ici");
		}

		average /= total;

		tmp->average = average;

		char n[SIZE_MAX] = "";
		char *name = n;

		strcpy(name, tmp->name);
		strcat(name, ".bmp");

		if (print_all) { // option d active
			write_bitmap_sdl(tmp, name);
		}

		log_info("Fin calcul de fractales");
	}

	return (void *) tmp;

	error:
		free(tmp);
		exit(EXIT_FAILURE);
}
