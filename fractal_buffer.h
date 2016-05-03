#ifndef _FRACTAL_BUFFER_H
#define _FRACTAL_BUFFER_H

/*
 * buffer_node_t est une liste doublement chainee, c'est un buffer de
 * taille maximale max_threads
 * @next: element suivant, NULL si fin de liste
 * @previous: element precedent, NULL si debut de liste
 * @fract: element courant.
 */
typedef struct {
    buffer_node_t *next;
    buffer_node_t *previous;
    fractal_t *fract;
} buffer_node_t;

/*
 * new_queue cree un nouveau buffer de type buffer_node_t
 * @return: retourne un pointeur vers la liste
 */
buffer_node_t *new_queue();
/*
 * enqueue ajoute un noeud a l'avant du buffer.
 * @new_fract: structure fractal a ajouter a la liste
 * @return: 0 si le noeud est ajoute a l'avant de la liste,
 *         -1 si une erreur apparait.
 */
int enqueue(fractal_t *new_fract);

/*
 * dequeue enleve un element a la fin du buffer.
 * @return: la structure fractal enlevee du buffer.
 *          NULL si buffer vide
 */
fractal_t *dequeue();

/*
 * free_list libere tous les noeuds d'une liste
 * @list: pointeur vers le debut d'une liste doublement chainee
 */
void free_list(buffer_node_t **list);

/*
 * print_fractal affiche la fractale
 */
void print_fractal(const fractal_t *fract);
/*
 * print_buffer affiche le contenu du buffer
 */
void print_buffer();

#endif
