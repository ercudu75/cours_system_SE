#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

typedef struct etudiant
{
    int age;
    char name[50];
    char prenom[50];
} etudiant;

int main(void)
{
    etudiant p, k;
    int fd;
    char *pathname = "text1.txt";

    if ((fd = open(pathname, O_CREAT | O_RDWR, 0644)) == -1)
    {
        perror("open");
        return (-1);
    }

    p.age = 21;
    strcpy(p.name, "ilyass");
    strcpy(p.prenom, "bentalha");

	write(fd, &p, sizeof(p));
    lseek(fd, 0, SEEK_SET);
	read(fd, &k, sizeof(k));
    printf("name %s surname %s age %d\n", k.name, k.prenom, k.age);
    close(fd);

    return (0);
}
