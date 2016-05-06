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

buffer_node_t *head = NULL;
buffer_node_t *tail = NULL;
fractal_t *fractal_fav = NULL;

int buffer_size = 0;
int max_threads = 1;
bool print_all = false;
double best_average = 0;

int count_inputs = 0;
int reader_threads = 0;

pthread_mutex_t mutex_main;
pthread_mutex_t mutex_reader;
pthread_mutex_t mutex_calculator;
sem_t empty;
sem_t full;
pthread_mutex_t mutex_count;
pthread_mutex_t mutex_reader;

int main(int argc, char *argv[])
{
	const char *fileOut = argv[argc]; // output file's name
	get_options_and_count_inputs(argc, argv);

	if (argc == 1) {
		return -1; // no arguments
	}
	if (count_inputs == 0)
		return -1; //no files to open

	int err = 0;
	int i = 0;
	int n = 0;
	// threads in MAIN
	pthread_t pthread_reader[argc-2]; //max argc-2 fichier a lire
	pthread_t pthread_calculator[max_threads];
	pthread_mutex_init(&mutex_main, NULL); // pour dans le main

	// threads in READER
	pthread_mutex_init(&mutex_reader, NULL); // pour dans la fonction reader
	sem_init(&empty, 0, max_threads); // empty buffer

	//threads in CALCULATOR
	pthread_mutex_init(&mutex_calculator, NULL);
	sem_init(&full, 0, 0); // empty buffer

	// // Creation des threads reader

	for (i = 1; i < argc - 1; i++) {
		log_info("Creating reader threads");
		if ( strcmp(argv[i], ARGOPT_D) == 0) {
		} else if ( strcmp(argv[i], ARGOPT_MAXTHREADS) == 0) {
			i++;
		} else {
			// sem_wait(&empty);
			check(!pthread_create(&(pthread_reader[count_inputs]), NULL,
					&reader, (void *) (argv[i])),
					"Failed to create reader pthread");
			// if (err != 0) {
			// 	error(err,err,"pthread_create reader");
			// }
			pthread_mutex_lock(&mutex_reader);
			reader_threads++;
			pthread_mutex_unlock(&mutex_reader);
			// sem_post(&full);
		}
	}
	log_info("There are %d reader threads.", reader_threads);

	for (size_t i = 0; i < max_threads; i++) {
		log_info("Creating calculator threads");
		// pthread_mutex_lock(&mutex_main);
		check(!pthread_create(&(pthread_calculator[i]), NULL,
				&calculator, NULL), "Failed to create calculator pthread.");
		// pthread_mutex_unlock(&mutex_main);
	}

	return 0;

	error:
	exit(EXIT_FAILURE);
}

static void get_options_and_count_inputs(int argc, char *argv[])
{
	int i = 0;

	for (i = 1; i < argc - 1; i++) {
		if ( strcmp(argv[i], ARGOPT_D) == 0) {
			print_all = true;
			log_info("-d option used.");
		} else if ( strcmp(argv[i], ARGOPT_MAXTHREADS) == 0) {
			i++;
			if (i == argc)
				break;
			max_threads = atoi(argv[i]);
			log_info("--maxthreads option used, n = %d.", max_threads);
		} else {
			count_inputs++;
		}
	}
	log_info("There are %d inputs.", count_inputs);
}
