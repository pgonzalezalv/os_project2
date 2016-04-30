#ifndef _MAIN_H
#define _MAIN_H

#define MAX_BUFFER_SIZE 10 // taille par defaut, si on a pas de --maxthreads

extern struct buffer_node *buffer;

/*
 * reader lit un fichier sur l'entree standard et cree des fractales.
 * @fichier: le fichier a lire
 * @return: 0 si on a atteint la fin du fichier sans erreur,
 *          1 sinon.
 *
 * commentaires : Il faut un mutex pour chaque ligne lu
 */
int reader(char *fichier);

/*
 * calculator description
 * @fract:
 * @return:
 */
int calculator(fractal_t *fract);



#endif
