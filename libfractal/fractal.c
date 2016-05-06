#include <stdlib.h>
#include <string.h>

#include "../dbg.h"
#include "fractal.h"

fractal_t *fractal_new(const char *name, int width, int height, double a, double b)
{
    fractal_t *f_new = malloc(sizeof(fractal_t));
    check_mem(f_new);

    int n = 65;
    strncpy(f_new->name, name, (size_t) n);

    f_new->value = (int *)malloc(height * width * sizeof(int));
    check_mem(f_new);

    f_new->w = width;
    f_new->h = height;
    f_new->a = a;
    f_new->b = b;

    return f_new;

    error:
        if(f_new) free(f_new);
        if(f_new->value) fractal_free(f_new->value);
        exit(EXIT_FAILURE);
}

void fractal_free(fractal_t *f)
{
    free(f->value);
    free(f);
}

const char *fractal_get_name(const fractal_t *f)
{
    return f->name;
}

int fractal_get_value(const fractal_t *f, int x, int y)
{
    int w = fractal_get_width(f);
    int offset = (x-1) + (y-1) * w;
    return f->value[offset];
}

void fractal_set_value(fractal_t *f, int x, int y, int val)
{
    int w = fractal_get_width(f);
    int offset = (x-1) + (y-1) * w;
    f->value[offset] = val;
}

int fractal_get_width(const fractal_t *f)
{
    return f->w;
}

int fractal_get_height(const fractal_t *f)
{
    return f->h;
}

double fractal_get_a(const fractal_t *f)
{
    return f->a;
}

double fractal_get_b(const fractal_t *f)
{
    return f->b;
}
