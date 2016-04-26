#ifndef _MAIN_H
#define _MAIN_H

#define MAX_BUFFER_SIZE 10 // taille par defaut, si on a pas de --maxthreads

/*
 * Buffer de taille maximale MAX_BUFFER_SIZE
 * Liste doublement chainee.
 */
struct buffer_node {
  struct fractal *next;
  struct fractal *previous;
  struct fractal *current;
}

int reader(const *char fichier);
int push(buffer_node **listStart, struct fractal *new_fract);
struct fract *pop(buffer_node **listEnd);

#endif
