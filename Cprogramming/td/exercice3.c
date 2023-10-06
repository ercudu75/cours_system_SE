#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int i, x = 10, m, j;

	i = fork(); //p2
	if (i == 0)
	{
		j = fork(); //p3
		if (j == 0)
		{
			x = x + 2;
			exit(x);
		}
		wait(&m);
		x = m / 256; //m =256 * x
		x += 3;
	}
	else
	{
		//p1
		wait(&m);
		x = m /256;
		printf("x=%d\n", x);
	}
}
