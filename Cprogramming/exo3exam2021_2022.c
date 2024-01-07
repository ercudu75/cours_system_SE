#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>



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
