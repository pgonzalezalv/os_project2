#ifndef _MAIN_H
#define _MAIN_H

#define MAX_BUFFER_SIZE 10 // taille par defaut, si on a pas de --maxthreads

/*
 * struct buffer_node est une liste doublement chainee, c'est un buffer de
 * taille maximale MAX_BUFFER_SIZE
 * @next: element suivant, NULL si fin de liste
 * @previous: element precedent, NULL si debut de liste
 * @current: element courant.
 */
struct buffer_node{
  struct buffer_node *next;
  struct buffer_node *previous;
  struct fractal *current;
};

/*
 * reader lit un fichier sur l'entree standard et creer des fractales.
 * @fichier: le fichier a lire
 * @return: 0 si on a atteint las fin du fichier sans erreur,
 *          1 sinon.
 *
 * commentaires : Il faut un mutex pour chaque ligne lu
 */
int reader(const char *fichier);

/*
 * calculator description
 * @fract:
 * @return:
 */
int calculator(struct fractal *fract);

/*
 * push ajoute un noeud a l'avant du buffer.
 * @arg : prend comme argument un pointeur vers le debut d'une liste
 *        doublement chainee et une structure fractal.
 * @return : 0 si le noeud est ajoute a l'avant de la liste,
 *           -1 si une erreur apparait.
 */
int push(struct buffer_node **listStart, struct fractal *new_fract);

/*
 * pop enleve un element a la fin du buffer.
 * @arg : prend comme argument un pointeur vers la fin d'une liste doublement
 *        chainee.
 * @return : la structure fractal enlevee du buffer.
 */
struct fract *pop(struct buffer_node **listEnd);

#endif
