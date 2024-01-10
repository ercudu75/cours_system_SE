#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(void)
{
	char rd[80];
	int fd;
	char *pathname = "fich_pipe.txt";

	mkfifo(pathname, 0777);

	if ((fd = open(pathname, O_CREAT | O_RDONLY, 0777)) == -1)
	{
		perror("open");
		return(-1);
	}

	lseek(fd, -80, SEEK_END);
	read(fd, rd, 80);

	printf("last information %s", rd);

	close(fd);
	return (0);
}
