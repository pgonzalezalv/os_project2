#include <error.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libfractal/fractal.h"
#include "main.h"

struct buffer_node *buffer;

int testQueue()
{
    buffer = NULL;
    StartB = buffer;
    EndB = buffer; // ON traite pas encore le cas où la liste est NULL de base !!! EndB doit pas rester sur NULL
    
}
