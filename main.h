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
int reader(char *fichier);

/*
 * calculator description
 * @fract:
 * @return:
 */
int calculator(struct fractal *fract);

/*
 * enqueue ajoute un noeud a l'avant du buffer.
 * @new_fract: structure fractal a ajouter a la liste
 * @return: 0 si le noeud est ajoute a l'avant de la liste,
 *         -1 si une erreur apparait.
 */
int enqueue(struct fractal *new_fract);

/*
 * dequeue enleve un element a la fin du buffer.
 * @return: la structure fractal enlevee du buffer.
 *          NULL si buffer vide
 */
struct fractal* dequeue();

/*
 * free_list libere tous les noeuds d'une liste
 * @list: pointeur vers le debut d'une liste doublement chainee
 */
void free_list(struct buffer_node **list);

/*
 * print_fractal affiche la fractale
 */
void print_fractal(const struct fractal *fract);
/*
 * print_buffer affiche le contenu du buffer
 */
void print_buffer();

#endif
