#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
/**
 * this second program read first then write in the
 * same pipe of the fifo1.txt
*/
int main(void)
{
	int fd;
	char wr1[80];
	char rd1[80];
	char *pathname = "fifo1.txt";

	mkfifo(pathname, 0666);
	while (1)
	{
		if ((fd = open(pathname, O_RDONLY)) == -1)
		{
			perror("open");
			return (-1);
		}
		read(fd, rd1, sizeof(rd1));
		printf("User1: %s\n", rd1);
		close(fd);

		if ((fd = open(pathname, O_WRONLY)) == -1)
		{
			perror("open");
			return (-1);
		}
		fgets(wr1, 80, stdin);
		write(fd, wr1, strlen(wr1)+1);
		close(fd);
	}
	return (0);
}
