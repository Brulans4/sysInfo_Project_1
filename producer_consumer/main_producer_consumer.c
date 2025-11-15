#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>


#include "buffer.h"
#include "producer.h"
#include "consumer.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("expected 1 arguments but got %d\n", argc - 1);
        exit(EXIT_FAILURE);
    }

    int nb_threads = atoi(argv[1]);
    if (nb_threads <= 0) {
        exit(EXIT_FAILURE);
    }

    int nb_prod = nb_threads / 2;
    int nb_cons = nb_threads - nb_prod;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_t* producers = malloc(nb_prod * sizeof(pthread_t));
    pthread_t* consumers = malloc(nb_cons * sizeof(pthread_t));

    if (!producers || !consumers)
        exit(EXIT_FAILURE);

    for (int i = 0; i < nb_prod; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    for (int i = 0; i < nb_cons; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    /* ---- Join ---- */
    for (int i = 0; i < nb_prod; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < nb_cons; i++) {
        pthread_join(consumers[i], NULL);
    }



    free(producers);
    free(consumers);

    return 0;
}
