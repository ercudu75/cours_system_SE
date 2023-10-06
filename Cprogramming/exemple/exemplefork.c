#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	int i, n = 0;
	int s1 = 0, s2 = 0, S;

	i = fork();
	if (i == 0)
	{
		for(i = 1; i <= 10; i++)
			s1 += i;
		exit(n);
	}
	else
	{
		wait(&n);
		for(i = 11; i <= 20; i++)
			s2 += i;
		s2 += s1;
	}
	printf("%d", s2);
	return 0;
}
