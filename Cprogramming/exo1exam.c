#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>


typedef struct threadinfo
{
	int id;
}threadinfo;

threadinfo id1, id2;

void *fucntion(void *arg)
{
	threadinfo *val = (threadinfo *)arg;
	while (1)
	{
		if (val->id == 1)
		{
			printf("thread1 \n");
		}
		else
		{
			printf("thread2 \n");
		}
	}
}

int main(void)
{
	pthread_t t1, t2;

	id1.id = 1;
	id2.id = 2;

	pthread_create(&t1, NULL, fucntion, (void *)&id1);
	pthread_create(&t2, NULL, fucntion, (void *)&id2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return (0);
}
