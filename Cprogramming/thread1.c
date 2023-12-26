#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define N 6

int tab[N] = { 1, 5 , 6 , 7, 9, 8};
int resulatat1 = 0, resulatat2 = 0, resulatat;

void *somme1(void *arg)
{
	int i;

	for (i = 0; i < N/2; i++)
		resulatat1 += tab[i];

}
void *somme2(void *arg)
{
	int i;

	for (i = N/2; i < N; i++)
		resulatat2 += tab[i];
}
int main(void)
{
	int i;
	pthread_t somme_id[2];

	pthread_create(&somme_id[0], NULL, somme1, NULL);
	pthread_create(&somme_id[1], NULL, somme2, NULL);

	for (i = 0; i < 2; i++)
		pthread_join(somme_id[i], NULL);

	resulatat = resulatat1 + resulatat2;

	printf("le resultat %d", resulatat);
}
