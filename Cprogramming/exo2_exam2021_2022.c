#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


typedef struct personne
{
	int age;
	char *name;
}personne;


int main(void)
{
	personne tab[5], tab2[5], tab3[5];
	int n, j, i;
	int fd1[2], fd2[2];
	int fd;
	char *pathname = "fich_personne";

	pipe(fd1);
	pipe(fd2);
	for (i = 0; i < 5; i++)
	{
		tab[i].name = (char *)malloc(100);
		printf("entrer le nom et l'age pour %i\n", i);
		scanf("%d %s", &tab[i].age, tab[i].name);
	}

	if ((n = fork()) == -1)
	{
		perror("fork");
		return (-1);
	}
	if (n == 0)
	{
		close(fd1[1]);
		read(fd1[0], tab2, sizeof(personne) *5);
		close(fd1[0]);
		if ((fd = open(pathname, O_CREAT | O_RDWR, 0777)) == -1)
		{
			perror("open");
			return (-1);
		}
		write(fd, tab2, sizeof(personne) * 5);
		close(fd);
	}
	else
	{
		for (i = 0; i < 5; i++)
		{
			if (tab[i].age < 20)
			{
				close(fd1[0]);
				write(fd1[1], &tab[i], sizeof(personne) * 5);
				close(fd1[1]);
			}
			else
			{
				close(fd2[0]);
				write(fd2[1], &tab[i], sizeof(personne) * 5);
				close(fd2[1]);
			}
		}
		j = fork();
		if (j == 0)
		{
			close(fd2[1]);
			read(fd2[0], tab3, sizeof(personne) * 5);
			close(fd2[0]);
			if ((fd = open(pathname, O_CREAT | O_RDWR, 0777)) == -1)
			{
				perror("open");
				return (-1);
			}
			write(fd, tab3, sizeof(personne) * 5);
			close(fd);
		}
	}
	return (0);
}
