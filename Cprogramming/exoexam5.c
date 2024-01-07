#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 500


int fil;

void *execute_command(void *arg)
{
	char *ar = (char *)arg;
	char *pathname = "command.txt";

	if ((fil = open(pathname, O_CREAT | O_WRONLY, 0666)) == -1)
	{
		perror("open");
	}

	if (dup2(fil, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fil);
        pthread_exit(NULL);
    }

	system(ar);
	close(fil);
	pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
	int i, n;
	int fd[2];
	char *command[2];
	char read_command[2][MAX_COMMAND_LENGTH];
	pthread_t id1, id2;

	pipe(fd);
	if (argc != 3)
	{
		printf("no arguments\n");
		return (-1);
	}

	command[0] = strdup(argv[1]);
	command[1] = strdup(argv[2]);

	for (int j = 0; j < 2; j++)
	{
        printf("Read Command %d: %s\n", j + 1, command[j]);
    }
	i = fork();
	if (i == 0)
	{
		close(fd[1]);
		read(fd[0], read_command[0], MAX_COMMAND_LENGTH);
		read(fd[0], read_command[1], MAX_COMMAND_LENGTH);
		close(fd[0]);
		for (int j = 0; j < 2; j++)
			printf("read Command %d: %s\n", j + 1, read_command[j]);
		pthread_create(&id1, NULL, execute_command, (void *)read_command[0]);
		pthread_create(&id2, NULL, execute_command, (void *)read_command[1]);
		pthread_join(id1, NULL);
		pthread_join(id2, NULL);
		exit(1);
	}
	else
	{
		close(fd[0]);
		write(fd[1], command[0], strlen(command[0]) + 1);
		write(fd[1], command[1], strlen(command[1]) + 1);
		close(fd[1]);
		wait(&n);
	}

}
