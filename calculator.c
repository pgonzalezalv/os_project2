#include "calculator.h"
#include "libfractal/fractal.h"
#include "../main.h"

int calculator(fractal_t *f)
{

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
			value = fractal_compute_value(f, x, y);
			sum += value;
		}
	}

	average = sum / count;

	if (print_all) { // option d active
		write_bitmap_sdl(f, f->name);
	}

	if (ave_max < average) {
		ave_max = average;

		if(fractal_fav != NULL)
			free(fractal_fav);

		fractal_fav = f;
	} else {
		fractal_free(f);
	}

	return 0;
}
