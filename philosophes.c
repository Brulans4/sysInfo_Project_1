#include "philosophes.h"

pthread_t *chaises;
pthread_mutex_t *baguettes;
int nbPhilosophes;

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("expected 1 arguments but got %d\n", argc - 1);
        exit(1);
    }
    nbPhilosophes = atoi(argv[1]);

    chaises = (pthread_t *)(malloc(nbPhilosophes * sizeof(pthread_t)));
    baguettes = (pthread_mutex_t *)(malloc(nbPhilosophes * sizeof(pthread_mutex_t)));

    for (int i = 0; i < nbPhilosophes; i++)
    {
        pthread_mutex_init(&baguettes[i], NULL);
    }

    for (int i = 0; i < nbPhilosophes; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&chaises[i], NULL, philosophe, id);
    }

    for (int i = 0; i < nbPhilosophes; i++)
    {
        pthread_join(chaises[i], NULL);
    }
    exit(0);
}

void* philosophe(void *arg)
{
    int *id = (int *)(arg);

    int left = *id + 1 == nbPhilosophes ? 0 : *id;
    int right = *id + 1 == nbPhilosophes ? *id : *id + 1;

    int countCycle = 0;

    while (countCycle < MAX_CYCLES)
    {
        // printf("philosophe %d pense\n", *id);

        pthread_mutex_lock(&baguettes[left]);
        pthread_mutex_lock(&baguettes[right]);

        // printf("philosophe %d mange\n", *id);

        pthread_mutex_unlock(&baguettes[left]);
        pthread_mutex_unlock(&baguettes[right]);

        countCycle ++;
    }
    return NULL;
}
