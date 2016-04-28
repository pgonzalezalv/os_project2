#ifndef _MAIN_H
#define _MAIN_H

#define MAX_BUFFER_SIZE 10 // taille par defaut, si on a pas de --maxthreads

extern struct buffer_node *buffer;

/*
 * struct buffer_node est une liste doublement chainee, c'est un buffer de
 * taille maximale MAX_BUFFER_SIZE
 * @next: element suivant, NULL si fin de liste
 * @previous: element precedent, NULL si debut de liste
 * @fract: element courant.
 */
struct buffer_node{
  struct buffer_node *next;
  struct buffer_node *previous;
  struct fractal *fract;
};

/*
 * reader lit un fichier sur l'entree standard et cree des fractales.
 * @fichier: le fichier a lire
 * @return: 0 si on a atteint la fin du fichier sans erreur,
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
 * @list: pointeur vers le debut d'une liste doublement chainee
 * @new_fract: structure fractal a ajouter a la liste
 * @return: 0 si le noeud est ajoute a l'avant de la liste,
 *         -1 si une erreur apparait.
 */
int push(struct buffer_node **list, struct fractal *new_fract);

/*
 * pop enleve un element a la fin du buffer.
 * @list: pointeur vers la fin d'une liste doublement
 *        chainee.
 * @return: la structure fractal enlevee du buffer.
 */
struct fractal* pop(struct buffer_node **list);

/*
 * free_list libere tous les noeuds d'une liste
 * @list: pointeur vers le debut d'une liste doublement chainee
 */
void free_list(struct buffer_node **list);

#endif
