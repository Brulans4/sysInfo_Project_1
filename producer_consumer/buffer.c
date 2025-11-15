#include "buffer.h"

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int consumerPointer = 0;
int producerPointer = 0;
unsigned long buffer[BUFFER_SIZE];

void insert_item(unsigned long tid, int pointer) {
    buffer[pointer % BUFFER_SIZE] = tid;
}

unsigned long remove_item(int pointer) {
    unsigned long tmp = buffer[pointer % BUFFER_SIZE];
    buffer[pointer % BUFFER_SIZE] = 0;
    return tmp;
}
