#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        if (fork() == 0) {
            int fd0 = open(argv[4], O_RDONLY);
            dup2(fd0, 0);
            close(fd0);
            execlp(argv[1], argv[1], NULL);
            exit(1);
        }
        int status;
        wait(&status);
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            if (fork() == 0) {
                execlp(argv[2], argv[2], NULL);
                exit(1);
            }
            wait(NULL);
            exit(0);
        }
        exit(0);
    }
    if (fork() == 0) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        int fd1 = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0700);
        dup2(fd1, 1);
        close(fd1);
        execlp(argv[3], argv[3], NULL);
        exit(1);
    }
    while (wait(NULL) != -1) {
    }
    close(fd[0]);
    close(fd[1]);
    return 0;
}