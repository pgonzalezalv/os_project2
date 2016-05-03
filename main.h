#ifndef _MAIN_H
#define _MAIN_H

/**
 * This file contains all the global variables used throughout the program.
 */

// extern struct buffer_node_t *buffer;

// The number of calculations threads allowed by the command-line argument
extern bool print_all;
extern int max_threads;

/* Checks for -d & --maxthreads n options and sets their values
 * @argc: number of input arguments argv
 * @argv: command line input arguments (includes name of executable)
 */
void get_options(int argc, char *argv[]);

#endif
