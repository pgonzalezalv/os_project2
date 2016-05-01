#include <assert.h>
#include <error.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "libfractal/fractal.h"
#include "calculator.h"
#include "fractal_buffer.h"
#include "main.h"
#include "reader.h"

//struct buffer_node_t *buffer;
struct buffer_node_t *head = NULL;
struct buffer_node_t *tail = NULL;
int buffer_size = 0;

int main(int argc, char *argv[])
{
	get_options(argc, argv);

    if (optind < argc) { // file arguments
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("reading %s ", argv[optind++]);
			reader(argv[optind]);
        printf("\n");
    }

	int test = 0;

	// printf("Reading : %s\n", argv[1]);
	// test = reader(argv[1]);


	// il faut un sémaphore pour multi-threader la fonction reader
	// sem_t sem;
	// sem_init(&sem, 0, MAX_BUFFER_SIZE);

	/* TO DO */

	// sem_destroy(&sem);

	return 0;
}

void get_options(int argc, char *argv[])
{
	int c = 0;
    int digit_optind = 0;
	int num_calculator = 0;


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
					num_calculator = atoi(optarg);
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
            break;

            case '?':
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
}
