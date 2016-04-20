#include <stdlib.h>
#include "fractal.h"

struct fractal *fractal_new(const char *name, int width, int height, double a, double b)
{
    struct fractal *f_new = malloc(sizeof(struct fractal));

    int i = 0;
    for(i = 0; name[i] != '\0'; i++)
        f_new->name[i] = name[i];
    f_new->name[i] = '\0';

    f_new->value = (int *)malloc(height * width * sizeof(int));
    f_new->w = width;
    f_new->h = height;
    f_new->a = a;
    f_new->b = b;

    return NULL;
}

void fractal_free(struct fractal *f)
{
    free(f->value);
    free(f);
}

const char *fractal_get_name(const struct fractal *f)
{
    return f->name;
}

int fractal_get_value(const struct fractal *f, int x, int y)
{
    int w = fractal_get_width(f);
    int offset = (x-1) + (y-1) * w;
    return f->value[offset];
}

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
    int w = fractal_get_width(f);
    int offset = (x-1) + (y-1) * w;
    f->value[offset] = val;
}

int fractal_get_width(const struct fractal *f)
{
    return f->w;
}

int fractal_get_height(const struct fractal *f)
{
    return f->h;
}

double fractal_get_a(const struct fractal *f)
{
    return f->a;
}

double fractal_get_b(const struct fractal *f)
{
    return f->b;
}
