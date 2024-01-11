#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/wait.h>
#define N 6

pthread_t t1, t2, t3;
sem_t writing, reading;
int fd[2];

void *ecrire(void *arg)
{
	int n;
	char *pathname = "fich_exo";
	int tab[N] = {1, 2, 9, 8, 0, -7};

	if ((n = open(pathname, O_CREAT | O_RDWR, 0777)) == -1)
	{
		perror("open");
		exit(1);
	}
	sem_wait(&writing);
	write(n, tab, sizeof(tab));
	close(n);
	sem_post(&reading);
}

void *lecture(void *arg)
{
	int n;
	char *pathname = "fich_exo";
	int tab[N];

	if ((n = open(pathname, O_CREAT | O_RDONLY, 0777)) == -1)
	{
		perror("open");
		exit(1);
	}
	sem_wait(&reading);
	read(n, tab, sizeof(tab));
	close(n);
	close(fd[0]);
	write(fd[1], tab, sizeof(tab));
	close(fd[1]);
}

void *ecrite_fichier(void *arg)
{
	int n;
	int tab[N];
	char *pathname = "fich2_exo";

	close(fd[1]);
	read(fd[0], tab, sizeof(tab));
	close(fd[0]);

	if ((n = open(pathname, O_CREAT | O_RDONLY, 0777)) == -1)
	{
		perror("open");
		exit(1);
	}
	write(n, tab, sizeof(tab));
	close(n);
}

int main(void)
{
	int i;
	sem_init(&writing, 1, 1);
	sem_init(&reading, 1, 0);
	i = fork();
	if (i == 0)
	{
		pthread_create(&t3, NULL, ecrite_fichier, NULL);
		pthread_join(t3, NULL);
	}
	else
	{
		pthread_create(&t1, NULL, ecrire, NULL);
		pthread_create(&t2, NULL, lecture, NULL);

		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		wait(NULL);
	}
	sem_destroy(&writing);
    sem_destroy(&reading);
}
