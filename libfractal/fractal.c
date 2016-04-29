#include <stdlib.h>
#include <string.h>

#include "fractal.h"

struct fractal *fractal_new(const char *name, int width, int height, double a, double b)
{
    struct fractal *f_new = malloc(sizeof(struct fractal));
    if (f_new == NULL) {
        return NULL;
    }

    int n = 65;
    strncpy(f_new->name, name, (size_t) n);

    f_new->value = (int *)malloc(height * width * sizeof(int));
    if (f_new->value == NULL) {
        return NULL;
    }
    f_new->w = width;
    f_new->h = height;
    f_new->a = a;
    f_new->b = b;
    return f_new;
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
