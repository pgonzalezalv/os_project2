#ifndef _MAIN_H
#define _MAIN_H

#define MAX_BUFFER_SIZE 10

/*
 * Buffer de taille maximale MAX_BUFFER_SIZE
 * Liste doublement chainee.
 */
struct buffer {
  struct fractal *next;
  struct fractal *previous;
  struct fractal *current;
}

int reader(const *char fichier);

#endif
