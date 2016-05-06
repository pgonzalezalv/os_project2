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

void *calculator()
{
	sem_wait(&full);
	pthread_mutex_lock(&mutex_reader);
	fractal_t *f = dequeue();
	pthread_mutex_unlock(&mutex_reader);
	sem_post(&empty);

	if(f != NULL) {
		int x = 0;
		int y = 0;
		int width = fractal_get_width(f);;
		int height = fractal_get_height(f);

		double sum = 0;
		int count = width * height;

		int value = 0;
		double average = 0;

		pthread_mutex_lock(&mutex_calculator);
		log_info("Start calcul de fractales");
		for ( y = 0; y < height ; y++) {
			for( x = 0; x < width ; x++)  {
				value = fractal_compute_value(f, x, y);
				sum += value;
			}
			log_info("Vous etes ici");
		}

		average = sum / count;

		if (print_all) { // option d active
			write_bitmap_sdl(f, f->name);
		}
		if (best_average < average) {
			best_average = average;

			if(fractal_fav != NULL)
				free(fractal_fav);

			fractal_fav = f;
		} else {
			fractal_free(f);
		}
		log_info("Fin calcul de fractales");
		pthread_mutex_unlock(&mutex_calculator);
	}
	else if (count_inputs == 0) { // si le buffer est vide et pas d'autre fichier ne reste à être lu
		pthread_exit(NULL);
	}

	return NULL;
}
