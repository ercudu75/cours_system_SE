#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
/**
 * Exercice 1: Communication Simple Parent-Enfant
Objectif
Créer un processus enfant à l'aide de fork(). Utiliser pipe()
pour permettre une communication bidirectionnelle entre le processus
parent et l'enfant.
*/
int main(void)
{
	int fd1[2], fd2[2];
	int i, j;
	char response[50];
	char message[] = "welcome to hell";

	if (pipe(fd1) == -1 || pipe(fd2) == -1)
	{
		perror("pipe");
		return (-1);
	}

	j = fork();

	if (j == -1)
	{
		perror("fork");
		return (-1);
	}
	if (j == 0)
	{
		close(fd1[1]);
		read(fd1[0], response, sizeof(response));
		printf("Child received: %s\n", response);
		close(fd1[0]);

		char message2[] = "hell no i'm going back";
		write(fd2[1], message2, sizeof(message2));
		close(fd2[1]);
		exit(0);
	}
	else
	{
		close(fd1[0]);
		write(fd1[1], message, sizeof(message));
		close(fd1[1]);

		wait(&i);

		read(fd2[0], response, sizeof(response));
		printf("Parent received: %s\n", response);
		close(fd2[0]);

	}
}
