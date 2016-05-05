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
	pthread_mutex_lock(&mutex_calculator);
	fractal_t *f = dequeue();
	pthread_mutex_unlock(&mutex_calculator);
	sem_post(&empty);

	if(f != NULL) {
	int x = 0;
	int y = 0;
	int width = fractal_get_width(f);;
	int height = fractal_get_height(f);

	double sum = 0;
	int count = width * height;

	int value;
	double average;

	for ( y = 0; y < height ; y++) {
		for( x = 0; x < width ; x++)  {
			pthread_mutex_lock(&mutex_calculator);
			value = fractal_compute_value(f, x, y);
			sum += value;
			pthread_mutex_unlock(&mutex_calculator);
		}
	}

	pthread_mutex_lock(&mutex_calculator);
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
	pthread_mutex_unlock(&mutex_calculator);
	}
	else if (count_inputs == 0) { // si le buffer est vide et pas d'autre fichier ne reste à être lu
		pthread_exit(NULL);
	}
	calculator();
}
