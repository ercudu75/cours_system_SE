#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
/**
 * this frist program write first then read from the pipe
*/

int main(void)
{
	int fd;
	char *pathname;
	char wr[80];
	char rd[80];

	pathname = "fifo1.txt";
	mkfifo(pathname, 0666);
	while (1)
	{
		if ((fd = open(pathname, O_WRONLY)) == -1)
		{
			perror("open");
			return (-1);
		}
		/* first the program should write */
		fgets(wr, 80, stdin);
		write(fd, wr, strlen(wr)+1);
		close(fd);

		/* so now the should read the file*/
		if ((fd = open(pathname, O_RDONLY)) == -1)
		{
			perror("open");
			return (-1);
		}
		read(fd, rd, sizeof(rd));
		printf("User2: %s \n", rd);
		close(fd);
	}
	return (0);
}
