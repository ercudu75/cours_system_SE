#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

/**
 * do the same exercice but with
 * execl next time
*/
int main(int argc, char *argv[])
{
	int i;

	i = fork();
	if (i == 0)
	{
		wait(NULL);
		system("./prog");
	}
	else
	{
		system("gcc -o prog prog.c");
	}
}
