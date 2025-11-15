#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>

#define BUFFER_SIZE 8

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int consumerPointer = 0;
int producerPointer = 0;
unsigned long buffer[BUFFER_SIZE];   

// Prototypes
void* producer(void* arg);
void* consumer(void* arg);
void insert_item(unsigned long tid);
unsigned long remove_item();


// ------------------ MAIN --------------------

int main() {

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);   
    sem_init(&full, 0, 0);

    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}


// ------------------ PRODUCER --------------------

void* producer(void* arg) {

    unsigned long tid = (unsigned long)pthread_self();

    while (true) {

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        insert_item(tid);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

    }
}


// ------------------ CONSUMER --------------------

void* consumer(void* arg) {

    while (true) {

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        unsigned long tid = remove_item();
        printf("Consumer removed item from thread %lu\n", tid);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}


// ------------------ BUFFER OPS --------------------

void insert_item(unsigned long tid) {
    buffer[producerPointer % BUFFER_SIZE] = tid;
    producerPointer++;
}

unsigned long remove_item() {
    unsigned long tmp = buffer[consumerPointer % BUFFER_SIZE];
    buffer[consumerPointer % BUFFER_SIZE] = 0;
    consumerPointer++;
    return tmp;
}
