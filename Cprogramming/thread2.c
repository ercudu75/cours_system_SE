#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_t id1, id2;
int n = 2;

void *variab(void *arg)
{
	if (pthread_equal(pthread_self(), id1))
	{
		n++;
		printf("la valeur du n incrementer = %d\n", n);
	}
	else
	{
		n--;
		printf("la valeur du n decrementer = %d\n", n);
	}
}

int main(void)
{
	pthread_create(&id1, NULL, variab, NULL);
	pthread_create(&id2, NULL, variab, NULL);

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
}
