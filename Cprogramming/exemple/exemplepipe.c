#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    int i = fork();

    if (i == -1)
    {
        perror("fork");
        return 1;
    }

    if (i == 0)
    {
        close(fd[0]);
        int x;
        printf("Enter a value x: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            perror("write");
            return 2;
        }
        close(fd[1]);
	}
    else
    {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
        {
            perror("read");
            return 3;
        }
        close(fd[0]);
        printf("From child process: %d\n", y);
    }

    return 0;
}
