#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

pthread_t t1, t2;

typedef struct var
{
	int n;
}var;

var p1, p2;

void *somme(void *arg)
{
	int sum;

	sum  = p1.n + p2.n;
	printf("somme %d\n", sum);
	pthread_exit(NULL);
}

void *soustraction(void *arg)
{
	int sous;

	sous  = p1.n - p2.n;
	printf("soustraction %d\n", sous);
	pthread_exit(NULL);
}

int main(void)
{
	printf("first value \n");
	scanf("%d",  &p1.n);
	printf("second value \n");
	scanf("%d",  &p2.n);

	pthread_create(&t1, NULL, somme, NULL);
	pthread_create(&t2, NULL, soustraction, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return(0);
}
