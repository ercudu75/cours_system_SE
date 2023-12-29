#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>

pthread_t tr1, tr2, tr3;
sem_t sem1, sem2;
int tab[] = { 1, 9, 4, 2, 0};
int rd[5];
int df[2];

void *fichier(void *arg)
{
	int fd;
	int i;

	sem_wait(&sem1);
	if ((fd = open("fiche1.txt", O_CREAT | O_WRONLY, 0666)) == -1)
	{
		perror("open");
	}
	write(fd, tab, sizeof(tab));
	close(fd);
	sem_post(&sem2);
	sem_wait(&sem2);
	if ((fd = open("fiche1.txt", O_RDONLY)) == -1)
	{
		perror("open");
	}
	read(fd, rd, sizeof(rd));
	for (i = 0; i < 5; i++)
	{
		printf("%d ", rd[i]);
	}
	close(fd);
	close(df[0]);
	write(df[1], rd, sizeof(rd));
	close(df[1]);
	sem_post(&sem1);
}

void *fich(void *arg)
{
	int fd;
	int rd[5];

	if ((fd = open("fich2.txt", O_CREAT | O_WRONLY, 0666)) == -1)
	{
		perror("open");
	}
	close(df[1]);
	read(df[0], rd, sizeof(rd));
	close(df[0]);
	write(fd, rd, sizeof(rd));
	close(fd);
}


int main(void)
{
	int i, j;

	pipe(df);
	sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);

	i = fork();
	if (i == 0)
	{
		pthread_create(&tr3, NULL, fich, NULL);
		pthread_join(tr3, NULL);
	}
	else
	{
		pthread_create(&tr1, NULL, fichier, NULL);
		pthread_create(&tr2, NULL, fichier, NULL);

		pthread_join(tr1, NULL);
		pthread_join(tr2, NULL);
	}
}
