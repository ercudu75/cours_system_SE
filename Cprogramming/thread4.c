#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define N 4
int stock = 100;

void *client(void *arg)
{
	int val;

	while (1)
	{
		if (stock > 0)
		{
			printf("thread1: ");
			val = rand() % stock;
			printf("val %d \n", val);
			stock = stock - val;
			if (stock < 0)
				break;
			printf("stock %d \n", stock);
			sleep(1);
		}
	}
}
void *server(void *arg)
{
	while (1)
	{
		if (stock <= 0)
		{
			stock = 100;
			printf("stock is full now");
			break;
			sleep(1);
		}
	}
}
int main(void)
{
	int i;
	pthread_t id_client[N], id_server;

	for(i = 1; i <= 4; i++)
		pthread_create(&id_client[i], NULL, client, NULL);
	pthread_create(&id_server, NULL, server, NULL);

	for (i = 0; i < N; i++)
		pthread_join(id_client[i], NULL);
	sleep(1);

	pthread_join(id_server, NULL);
}
