#ifndef _MAIN_H
#define _MAIN_H

/**
 * This file contains all the global variables used throughout the program.
 */

// extern struct buffer_node_t *buffer;

// The number of calculations threads allowed by the command-line argument
extern bool print_all;
extern int max_threads;
extern double ave_max;
extern fractal_t *fractal_fav;
extern int count_files;
extern buffer_node_t *head;
extern buffer_node_t *tail;
extern int buffer_size;

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
