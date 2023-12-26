#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define N 6

pthread_t id1, id2;
int tab[N] = { 1, 5, 6, -9, 0, -1};

void *posneg(void *arg)
{
	int i;

	if (pthread_equal(pthread_self(), id1))
	{
		printf("thread1: ");
		for(i = 0; i < N; i++)
		{
			if (tab[i] >= 0)
				printf("%d ", tab[i]);
		}
		printf("\n");
	}
	else
	{
		printf("thread2: ");
		for(i = 0; i < N; i++)
		{
			if (tab[i] < 0)
				printf("%d ", tab[i]);
		}
		printf("\n");
	}
}

int main(void)
{
	pthread_create(&id1, NULL, posneg, NULL);
	pthread_create(&id2, NULL, posneg, NULL);

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
}
