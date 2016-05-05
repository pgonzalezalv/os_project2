#ifndef _MAIN_H
#define _MAIN_H

/**
 * This file contains all the global variables used throughout the program.
 */

// If d option is used, print_all is true, else false.
extern bool print_all;
// The number of calculations threads allowed by the command-line argument
extern int max_threads;
// The best average
extern double ave_max;
// The fractal with the best average
extern fractal_t *fractal_fav;
// The number of opened files
extern int count_files;
// The buffer size
extern int buffer_size;
// The head of the buffer
extern buffer_node_t *head;
// The tail of the buffer
extern buffer_node_t *tail;

extern pthread_mutex_t mutex_countf;
extern pthread_mutex_t mutex_reader;
extern pthread_mutex_t mutex_calculator;
extern sem_t empty;
extern sem_t full;


/* Checks for -d & --maxthreads n options and sets their values
 * @argc: number of input arguments argv
 * @argv: command line input arguments (includes name of executable)
 */
void get_options(int argc, char *argv[]);

#endif
