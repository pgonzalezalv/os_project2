#include <assert.h>
#include <error.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "calculator.h"
#include "dbg.h"
#include "libfractal/fractal.h"
#include "fractal_buffer.h"
#include "main.h"
#include "reader.h"

#define ARGOPT_D "-d"
#define ARGOPT_MAXTHREADS "--maxthreads"

bool print_all = false;
int max_threads = 1;
int count_files = 0;

int buffer_size = 0;
buffer_node_t *head = NULL;
buffer_node_t *tail = NULL;

int is_reading = 0;

double best_average = 0;
fractal_t *best = NULL;

pthread_mutex_t mutex_buffer;
pthread_mutex_t mutex_closing;
pthread_mutex_t mutex_best;
sem_t empty;
sem_t full;

pthread_t *reader_threads;
pthread_t *calculator_threads;

int main(int argc, char *argv[])
{
	const char *files[argc];
	const char *fileOut = argv[argc-1]; // output file's name

	get_options_and_is_reading(argc, argv);
	log_info("-d option used?");
	if (print_all) log_info("Yes.");
	else log_info("No.");
	log_info("%d calculations threads.", max_threads);
	log_info("There are %d inputs.", count_files);
	log_info("Output file is %s.", fileOut);

	int arg[max_threads];
	int err = 0;
	int i = 0;

	for (i = 0; i < count_files; i++) printf
	("Fichier de donnee n° %i : %s\n", i+1, files[i]);


	// Initializing semaphores & mutex
	pthread_mutex_init(&mutex_buffer, NULL);
	pthread_mutex_init(&mutex_closing, NULL);
	pthread_mutex_init(&mutex_best, NULL);
	sem_init(&empty, 0, max_threads); // empty buffer
	sem_init(&full, 0, 0); // empty buffer

	reader_threads = (pthread_t *) malloc(count_files * sizeof(pthread_t));
	calculator_threads = (pthread_t *) malloc(count_files * sizeof(pthread_t));

	log_info("Creating reader threads");
	for (i = 1; i < count_files; i++) {
		check(!pthread_create(&(reader_threads[is_reading]), NULL,
					&reader, (void *)files[i]),
					"Failed to create reader pthread");
	} log_info("There are %d open files.", is_reading);

	log_info("Creating calculator threads");
	for (i = 0; i < max_threads; i++) {
		check(!pthread_create(&(calculator_threads[i]), NULL,
				&calculator, &(arg[i])),
				"Failed to create calculator pthread.");
	}

	for (i = 0; i < max_threads; i++) {
		fractal_t *tmp;
		check(!pthread_join(calculator_threads[i], (void **) &tmp),
				"Join calculation thread problem %i.", i);
		if ( best == NULL) {
			best = tmp;
		} else if (best->average < tmp->average) {
			log_info("Gettting best of thread %i.", i);
			fractal_free((fractal_t *) best);
			best = (fractal_t *) tmp;
		} else {
			fractal_free(tmp);
		}
	}
	return 0;

	log_info("EXIT OF RETURN.");

	check(!write_bitmap_sdl(best, fileOut),
			"Error while writing best fractal");

	error:
		exit(EXIT_FAILURE);
}

static void get_options_and_is_reading(int argc, char *argv[])
{
	int i = 0;

	for (i = 1; i < argc - 1; i++) {
		if ( strcmp(argv[i], ARGOPT_D) == 0) {
			print_all = true;
		} else if ( strcmp(argv[i], ARGOPT_MAXTHREADS) == 0) {
			i++;
			if (i == argc)
				break;
			max_threads = atoi(argv[i]);
		} else {
			count_files++;
		}
	}
}
