#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define max_tab 10

int T[max_tab];
int g = 0;

void *producer(void *arg);
void *consumer(void *arg);

void *producer(void *arg)
{
    while (1)
    {
        int a = rand() % 100;
        T[g] = a;
        g = (g + 1) % max_tab;
    }
}

void *consumer(void *arg)
{
    while (1)
    {
        // Consume the produced values
        int value = T[g];
        printf("Consumed value: %d\n", value);
        g = (g + 1) % max_tab;
    }
}

int main()
{
    pthread_t clients[4];
    pthread_t producer_thread;
    int i = 0;

    while (i < 4)
    {
        pthread_create(&clients[i], NULL, consumer, NULL);
        pthread_join(clients[i], NULL);
        i++;
    }

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_join(producer_thread, NULL);

    return 0;
}
