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
	fractal_t fractal *f = NULL;

	while (isReading != 0) {

		f = dequeue();

		if(f != NULL) {
			int x = 0;
			int y = 0;
			int width = fractal_get_width(f);;
			int height = fractal_get_height(f);

			double sum = 0;
			int total = width * height;

			int value = 0;
			double average = 0;

			log_info("Start calcul de fractales");
			for ( y = 0; y < height ; y++) {
				for( x = 0; x < width ; x++)  {
					value = fractal_compute_value(f, x, y);
					average += value;
				}
				log_info("Vous etes ici");
			}

			average /= total;

			if (print_all) { // option d active
				write_bitmap_sdl(f, f->name);
			}
			if (best_average < average) {
				best_average = average;
				log_info("Et ici?");

				if(fractal_fav != NULL)
				free(fractal_fav);

				fractal_fav = f;
			} else {
				fractal_free(f);
			}
			log_info("Fin calcul de fractales");
		}
		else if (is_reading == 0) { // si le buffer est vide et pas d'autre fichier ne reste à être lu
		pthread_exit(NULL);
	}

	return NULL;
}
