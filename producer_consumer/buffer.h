#ifndef BUFFER_H
#define BUFFER_H

#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 8

extern pthread_mutex_t mutex;
extern sem_t empty;
extern sem_t full;

extern int consumerPointer;
extern int producerPointer;
extern unsigned long buffer[BUFFER_SIZE];

void insert_item(unsigned long tid, int temp);
unsigned long remove_item(int temp);

#endif
