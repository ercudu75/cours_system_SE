#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int i , x = 100;
	i = fork();
	printf("x = %d i = %d pid = %d ppid = %d\n", x, i, getpid(), getppid());
}
