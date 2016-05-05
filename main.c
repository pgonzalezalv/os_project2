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

buffer_node_t *head = NULL;
buffer_node_t *tail = NULL;
fractal_t *fractal_fav = NULL;

int buffer_size = 0;
int max_threads = 1;
bool print_all = false;
double best_average = 0;

int count_inputs = 0;

pthread_mutex_t mutex_main;
pthread_mutex_t mutex_reader;
pthread_mutex_t mutex_calculator;
sem_t empty;
sem_t full;

int main(int argc, char *argv[])
{
	const char *fileOut = argv[argc]; // output file's name
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

	get_options_and_count_inputs(argc, argv);

	// // Creation des threads reader

	for (i = 1; i < argc - 1; i++) {
		if ( strcmp(argv[i], "-d") == 0) {
		} else if ( strcmp(argv[i], "--maxthreads") == 0) {
			i++;
		} else {
			pthread_mutex_unlock(&mutex_main);
			err = pthread_create(&(pthread_reader[count_inputs]), NULL, &reader, &(argv[i]));
			check(err == 0, "Failed to create reader pthread, %d.", err);
			// if (err != 0) {
			// 	error(err,err,"pthread_create reader");
			// }
			count_inputs++;
			pthread_mutex_unlock(&mutex_main);
		}
	}
	log_info("There are %d inputs.", count_inputs);
	if (count_inputs == 0)
		return 0; //no files to open


	// // Creation des threads reader
	// if (optind < argc) { // file arguments
	//     log_info("Reading non-option ARGV-elements.");
	//     while (optind < argc)
	//         log_info("reading %s.", argv[optind++]);
	// 		// if ((strcmp(argv[optind], "-"))) {// reading on stdin
	// 		// 	printf("Hello\n");
	// 		// }
	// 		//reader(argv[optind]);
	//
	// 		pthread_mutex_unlock(&mutex_main);
	// 		err = pthread_create(&(pthread_reader[count_inputs]), NULL, &reader, &(argv[optind]));
	// 		check(err == 0, "Failed to create pthread, %d.", err)
	// 		// if (err != 0) {
	// 		// 	error(err,err,"pthread_create reader");
	// 		// }
	// 		log_info("Created thread #%d.", optind-1);
	// 		count_inputs++;
	// 		pthread_mutex_unlock(&mutex_main);
	//
	//     printf("\n");
	// }
	//
	// int n = 0;
	// err=0;
	// while(n<max_threads)
	// {
	// 	pthread_mutex_lock(&mutex_main);
	// 	err = pthread_create(&(pthread_calculator[n]), NULL, &calculator, NULL);
	// 	if (err != 0) {
	// 		error(err,err,"pthread_create calculator");
	// 	}
	// 	n++;
	// 	pthread_mutex_unlock(&mutex_main);
	// }

	err = pthread_create(&(pthread_calculator[n]), NULL, &calculator, NULL);
	check(err == 0, "Failed to create calculator pthread, %d.", err);
	n++;
	pthread_mutex_unlock(&mutex_main);

	return 0;

	error:
	exit(EXIT_FAILURE);
}

static void get_options_and_count_inputs(int argc, char *argv[])
{
	int i = 0;

	for (i = 1; i < argc - 1; i++) {
		if ( strcmp(argv[i], "-d") == 0) {
			print_all = true;
			log_info("-d option used.");
		} else if ( strcmp(argv[i], "--maxthreads") == 0) {
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
