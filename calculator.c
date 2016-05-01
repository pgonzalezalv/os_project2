#include "calculator.h"
#include "libfractal/fractal.h"

int calculator()
{

	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	fractal_t *toCompute = NULL;

	toCompute = dequeue();
	width = toCompute->width
	height = toCompute->height

	for ( x = 0; x < width ; x++) {
		for ( y = 0; y < height ; y++) {
			fractal_compute_value(toCompute, x, y);
		}
	}

	return 0;
}
