#ifndef _MAIN_H
#define _MAIN_H

/**
 * This file contains all the global variables used throughout the program.
 */

#define MAX_BUFFER_SIZE 10 // taille par defaut, si on a pas de --maxthreads

// extern struct buffer_node_t *buffer;

// The number of calculations threads allowed by the command-line argument
// extern bool
extern int num_calculator;

/* Checks for -d & --maxthreads n options and sets their values
 * @argc: number of input arguments argv
 * @argv: command line input arguments (includes name of executable)
 */
void get_options(int argc, char *argv[]);

#endif
