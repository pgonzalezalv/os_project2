#include "calculator.h"
#include "libfractal/fractal.h"

int calculator(fractal_t *f, int currentAve)
{

	int x = 0;
	int y = 0;
	int width = fractal_get_width(f);;
	int height = fractal_get_height(f);

	double sum = 0;
	int count = 0;

	int value;
	double average;

	//fractal_t *toCompute = NULL;

	//toCompute = dequeue(); 							// mettre ca dans le main
	//width = toCompute->width
	//height = toCompute->height

	for ( y = 0; y < height ; y++) {
		for( x = 0; x < width ; x++)  {
			value = fractal_compute_value(toCompute, x, y);
			fractal_set_value(f, value);
			sum += value;
			count++;
		}
	}

	if (currentAve < average)
	{
		//change fractal_fav
	}

	return 0;
}
