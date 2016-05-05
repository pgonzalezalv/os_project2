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
#include "fractal.h"
#include "fractal_buffer.h"
#include "main.h"
#include "reader.h"

buffer_node_t *head = NULL;
buffer_node_t *tail = NULL;
fractal_t *fractal_fav = NULL;

int buffer_size = 0;
int max_threads = 1;
bool print_all = false;
double ave_max = 0;

int count_files = 0;

pthread_mutex_t mutex_main;
pthread_mutex_t mutex_reader;
pthread_mutex_t mutex_calculator;
sem_t empty;
sem_t full;

int main(int argc, char *argv[])
{
	const char *fileOut = argv[argc-1]; // output file's name
	int err = 0;

	// threads in MAIN
	pthread_t pthread_reader[argc-2]; //max argc-2 fichier a lire
	pthread_t pthread_calculator[max_threads-1];
	pthread_mutex_init(&mutex_main,NULL); // pour dans le main

	// threads in READER
	pthread_mutex_init(&mutex_reader,NULL); // pour dans la fonction reader
	sem_init(&empty,0,max_threads);

	//threads in CALCULATOR

	pthread_mutex_init(&mutex_calculator,NULL);
	sem_init(&full,0,0);

	get_options(argc, argv);

	// Creation des threads reader
    if (optind < argc) { // file arguments
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("reading %s\n", argv[optind++]);
			// if ((strcmp(argv[optind], "-"))) {// reading on stdin
			// 	printf("Hello\n");
			// }
			printf("%d\n", optind);
			//reader(argv[optind]);

			pthread_mutex_unlock(&mutex_main);
			err = pthread_create(&(pthread_reader[count_files]), NULL, &reader, &(argv[optind]));
			if (err != 0) {
				error(err,err,"pthread_create reader");
			}
			count_files++;
			pthread_mutex_unlock(&mutex_main);

        printf("\n");
    }

	int n = 0;
	err=0;
	while(n<max_threads)
	{
		pthread_mutex_lock(&mutex_main);
		err = pthread_create(&(pthread_calculator[n]), NULL, &calculator, NULL);
		if (err != 0) {
			error(err,err,"pthread_create calculator");
		}
		n++;
		pthread_mutex_unlock(&mutex_main);
	}

	// printf("Reading : %s\n", argv[1]);
	// test = reader(argv[1]);


	// il faut un sémaphore pour multi-threader la fonction reader
	// sem_t sem;
	// sem_init(&sem, 0, max_threads);

	/* TO DO */

	// sem_destroy(&sem);

	return 0;
}

void get_options(int argc, char *argv[])
{
	int c = 0;
    int digit_optind = 0;

    while (true) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"maxthreads",     required_argument, 0,  0 },
            {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "d",
        				long_options, &option_index);
        if (c == -1)
            break; // no options, get out of while

        switch (c) {
            case 0: // --maxthread n option
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
					max_threads = atoi(optarg);
                printf("\n");
                break;

            case '0':
            case '1':
            case '2':
                if (digit_optind != 0 && digit_optind != this_option_optind)
                    printf("digits occur in two different argv-elements.\n");
                digit_optind = this_option_optind;
                printf("option %c\n", c);
                break;

            case 'd': // -d option
                printf("option d\n");
				print_all = true;

            break;

            case '?':
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
}
