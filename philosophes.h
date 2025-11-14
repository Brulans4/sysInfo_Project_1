#ifndef PHILOSOPHE_H
#define PHILOSOPHE_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_CYCLES 1000000

void* philosophe(void *arg);

#endif // PHILOSOPHE_H