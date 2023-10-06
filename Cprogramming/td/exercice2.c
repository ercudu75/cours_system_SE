#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int i, j;

	i = fork();
	j = fork();
	printf("i = %d j = %d pid = %d ppid = %d\n", i, j, getpid(), getppid());
}
