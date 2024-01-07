#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int t[10] = {1, -2 , 0, -5, -1, 20, 7, 60, 12, -100};
pthread_t t1, t2;

void *positive(void *arg)
{
	int i;

	printf("positve numbers\n");
	for (i = 0; i < 10; i++)
		if (t[i] >= 0)
			printf("%d, ", t[i]);
	printf("\n");
}
void *negative(void *arg)
{
	int i;

	printf("negative numbers\n");
	for (i = 0; i < 10; i++)
	{
		if (t[i] < 0)
			printf("%d, ", t[i]);
	}
	printf("\n");
}

int main(void)
{
	pthread_create(&t1, NULL, positive, NULL);
	pthread_create(&t2, NULL, negative, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}
