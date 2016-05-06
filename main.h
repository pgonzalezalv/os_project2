#ifndef _MAIN_H
#define _MAIN_H

/**
 * This file contains all the global variables used throughout the program.
 */

// If d option is used, print_all is true, else false.
extern bool print_all;
// The number of calculations threads allowed by the command-line argument
extern int max_threads;
// The number of files
extern int count_files;
// The fractal with the best average
extern int buffer_size;
// The head of the buffer
extern buffer_node_t *head;
// The tail of the buffer
extern buffer_node_t *tail;
// The number of opened files;
extern int is_reading;
// The best average
extern double best_average;
// The best fractal
extern fractal_t *best;


extern pthread_mutex_t mutex_buffer;
extern pthread_mutex_t mutex_closing;
extern pthread_mutex_t mutex_best;
extern sem_t empty;
extern sem_t full;

extern pthread_t *read_threads;
extern pthread_t *compute_threads;

/**
 * Checks for : -d option and set print_all to true if detected,
 *              --maxthreads n option and set max_threads to n if detected,
 *              number of input files and set is_reading value accordingly.
 * @argc: number of input arguments argv.
 * @argv: command line input arguments (includes name of executable).
 */
static void get_options_and_is_reading(int argc, char *argv[]);

#endif
