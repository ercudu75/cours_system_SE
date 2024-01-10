#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(void)
{
	int fd;
	char *pathname = "fich_pipe.txt";
	char wr[80];

	mkfifo(pathname, 0777);

	if((fd = open(pathname, O_CREAT | O_RDWR, 0777)) == -1)
	{
		perror("open");
		return (-1);
	}

	fgets(wr, 80, stdin);
	write(fd, wr, 80);
	close(fd);
	return (0);
}
