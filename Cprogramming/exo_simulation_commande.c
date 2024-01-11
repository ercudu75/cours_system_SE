#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd1[2], fd2[2];
    int cut_pid, grep_pid, wc_pid;

    pipe(fd1);
	pipe(fd2);

    cut_pid = fork();
    if (cut_pid == 0)
	{
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);

        dup2(fd1[1], STDOUT_FILENO);
        close(fd1[1]);

        execl("/usr/bin/cut", "cut", "-d", ":", "-f1,3", "/etc/passwd", NULL);
    }

    grep_pid = fork();
    if (grep_pid == 0)
	{
        close(fd1[1]);
        close(fd2[0]);

        dup2(fd1[0], STDIN_FILENO);
        close(fd1[0]);

        dup2(fd2[1], STDOUT_FILENO);
        close(fd2[1]);

        execl("/usr/bin/grep", "grep", "daemon", NULL);
    }

    wc_pid = fork();
    if (wc_pid == 0)
	{
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[1]);

        dup2(fd2[0], STDIN_FILENO);
        close(fd2[0]);

        execl("/usr/bin/wc", "wc", "-l", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    return (0);
}
