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
	char wr[] = "voici un message pour la premier fonction";
	char rd[80];

	pathname = "fifo1.txt";
	mkfifo(pathname, 0666);
	if ((fd = open(pathname, O_WRONLY)) == -1)
	{
		perror("open");
		return (-1);
	}
	/* first the program should write */
    write(fd, wr, sizeof(wr));
	close(fd);

	/* so now the should read the file*/
	if ((fd = open(pathname, O_RDONLY)) == -1)
	{
		perror("open");
		return (-1);
	}
	read(fd, rd, sizeof(rd));
	printf("message dans le file \n %s \n", rd);
	close(fd);
	return (0);
}
