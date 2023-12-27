#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

/**
 * For the person who's reading this take notes u and i
 * we may fucked in the exam if we didn't take this note
 * in consideration
 * if we want to use lseek be aware of the offset
 * lseek(int fildes, off_t offset, int whence);
 * int, double, and float, use sizeof(type)
 * in char just regular number because it take 1 bytes
*/
int main(void)
{
	int fd, i;
	char *pathname = "fileio.txt";
	int tab[] = { 1, 2, 9, -2, -9};
	int rd[5];

	if ((fd = open(pathname, O_RDWR)) == -1)
	{
		perror("open");
		return (-1);
	}
	write(fd, tab, sizeof(tab));
	close(fd);

	if ((fd = open(pathname, O_RDONLY)) == -1)
	{
		perror("open");
		return (-1);
	}
	lseek(fd, sizeof(int), SEEK_SET);
	read(fd, rd, sizeof(rd));
    for (i = 0; i < 5; i++) {
        printf("%d ", rd[i]);
    }
    close(fd);
}
