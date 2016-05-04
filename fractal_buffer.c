#include <stdio.h>
#include <stdlib.h>

#include "fractal.h"
#include "fractal_buffer.h"
#include "main.h"


buffer_node_t *new_queue()
{
    buffer_node_t *fractal_buffer = NULL;

    return fractal_buffer;
}

//int enqueue(buffer_node_t **list, fractal_t *new_fract){
int enqueue(fractal_t *new_fract)
{
	buffer_node_t *new;
	new = malloc(sizeof(*new));

	if (new == NULL) // malloc test
		return -1;

	new->fract = new_fract;
	new->next = head;
	new->previous = NULL;
	if (head == NULL) { // empty buffer
		head = new;
		tail = head;
	} else if (head != NULL) { // at least 1 element in buffer
		head->previous = new;
		head = new;
	}
	buffer_size++;

	return 0;
}

fractal_t *dequeue()
{
	if (tail == NULL){ // empty buffer
		printf("Error : buffer is empty\n");
		return NULL;
	}

	if (tail == head) // buffer has 1 element
		head = NULL;

	fractal_t *fract = NULL;
	buffer_node_t *toRemove = tail;

	fract = tail->fract;
	tail = tail->previous;
	tail->next = NULL;

	free(toRemove);
	buffer_size--;

	return fract;
}

void free_list(buffer_node_t **list)
{
	int i = 0;

	while (buffer_size != 0)
		dequeue();
}

void print_fractal(const fractal_t *fract)
{
	const char *n = fractal_get_name(fract);
	int w = fractal_get_width(fract);
	int h = fractal_get_height(fract);
	double a = fractal_get_a(fract);
	double b = fractal_get_b(fract);

	printf("printing fract : \n");
	printf("%s %d %d %lf %lf\n", n, w, h, a, b);
}

void print_buffer()
{
	buffer_node_t *current = head;
	while (current) {
		print_fractal(current->fract);
		current = current->next;
	}
}
