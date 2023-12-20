#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd1[2], fd2[2], fd3[2];
    pid_t i, j;
    int donnee[] = {1, 2, 3, 4};
    int modif[4];
    size_t size = sizeof(donnee);

    if (pipe(fd1) == -1 || pipe(fd2) == -1 || pipe(fd3) == -1)
	{
        perror("pipe");
        return (-1);
    }

    i = fork();

    if (i == 0)
	{
        read(fd1[0], modif, size);
        close(fd1[0]);

        for (int k = 0; k < 4; k++)
            modif[k] += 5;

        close(fd2[0]);
        write(fd2[1], modif, size);
        close(fd2[1]);
        exit(0);
    }
	else
	{
        close(fd1[0]);
        write(fd1[1], donnee, size);
        close(fd1[1]);

        j = fork();
        if (j == 0)
		{
            close(fd2[1]);
            read(fd2[0], modif, size);
            close(fd2[0]);

            for (int k = 0; k < 4; k++)
                modif[k] *= 2;

            close(fd3[0]);
            write(fd3[1], modif, size);
            close(fd3[1]);
            exit(0);
        }

        close(fd2[0]);
        close(fd2[1]);
        close(fd3[1]);

        wait(NULL);
        wait(NULL);

        read(fd3[0], modif, size);
        close(fd3[0]);

        printf("Parent received: ");
        for (int k = 0; k < 4; k++)
            printf("%d ", modif[k]);
        printf("\n");
    }

    return (0);
}
