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
	char wr1[] = "second program";
	char rd1[80];
	char *pathname = "fifo1.txt";

	mkfifo(pathname, 0666);
	if ((fd = open(pathname, O_RDONLY)) == -1)
	{
		perror("open");
		return (-1);
	}
	read(fd, rd1, sizeof(rd1));
	printf("programe 2 read \n %s \n", rd1);
	close(fd);

	if ((fd = open(pathname, O_WRONLY)) == -1)
	{
		perror("open");
		return (-1);
	}
	printf("is writing\n");
	write(fd, rd1, sizeof(rd1));
	close(fd);
	return (-1);
}
