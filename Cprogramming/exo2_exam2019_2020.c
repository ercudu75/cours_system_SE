#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


pthread_t fuite1, fuite2, remplis;
pthread_mutex_t lock;
int plein = 100;

void *fuite(void *arg)
{
	while (plein > 0 && plein <= 100)
	{
		pthread_mutex_lock(&lock);
		plein = plein - (rand() % 10);
		printf("here1");
		pthread_mutex_unlock(&lock);
	}
	if (plein == 0 || plein > 100)
	{
		exit(1);
	}
}
void *remplissage(void *arg)
{
	while (plein > 0 && plein < 100)
	{
		plein = plein + (rand() % 10);
		printf("here2");
	}
	if (plein == 0 || plein > 100)
	{
		exit(1);
	}
}

int main(void)
{
	pthread_mutex_init(&lock, NULL);
	pthread_create(&fuite1, NULL, fuite, NULL);
	pthread_create(&fuite2, NULL, fuite, NULL);
	pthread_create(&remplis, NULL, remplissage, NULL);

	pthread_join(fuite1, NULL);
	pthread_join(fuite2, NULL);
	pthread_join(remplis, NULL);

	pthread_mutex_destroy(&lock);

	return (0);
}
