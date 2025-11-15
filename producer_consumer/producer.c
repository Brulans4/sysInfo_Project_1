#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "buffer.h"
#include "producer.h"

void* producer(void* arg) {
    unsigned long tid = (unsigned long)pthread_self();

    while (producerPointer< 131072) {
        int temp;

        pthread_mutex_lock(&mutex);
        if (producerPointer >= 131072) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        producerPointer++;
        temp = producerPointer;
        pthread_mutex_unlock(&mutex);
        
        sem_wait(&empty);
    
        sem_post(&full);

        insert_item(tid, temp);

        for (int i = 0; i < 10000; i++);
    }

    return 0;
}
