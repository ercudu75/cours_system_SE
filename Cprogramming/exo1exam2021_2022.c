#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

#define N 5
pthread_t t1, t2;

int T[N] = {5, 4, 3, -1, 2};

void *man_tab(void *arg)
{
	if (pthread_equal(pthread_self(), t1))
	{
		for (int i = 0; i < N; i++)
		{
			T[i] = rand()%10;
		}
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			T[i+1] = rand()%10;
		}
	}
}


int main(void)
{
	pthread_create(&t1, NULL, man_tab, NULL);
	pthread_join(t1, NULL);
	pthread_create(&t2, NULL, man_tab, NULL);
	pthread_join(t2, NULL);

	for (int i = 0; i < N; i++)
    {
        printf("%d ", T[i]);
    }
	return (0);
}
