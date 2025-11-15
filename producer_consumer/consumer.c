#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "buffer.h"
#include "consumer.h"

void* consumer(void* arg) {
    while (1) {
        int temp;

        pthread_mutex_lock(&mutex);
        if (consumerPointer >= 131072) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        consumerPointer++;
        temp = consumerPointer;
        pthread_mutex_unlock(&mutex);
        
        sem_wait(&full);

        sem_post(&empty);

        remove_item(temp);
        for (int i = 0; i < 10000; i++);
    }

    return 0;
}
