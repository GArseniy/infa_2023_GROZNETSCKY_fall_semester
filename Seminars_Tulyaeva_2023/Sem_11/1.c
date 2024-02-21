#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    int pfd[2];
    pipe(pfd);

    pid_t pid1 = fork();

    if (!pid1) {
        dup2(pfd[1], 1);

        close(pfd[0]);
        close(pfd[1]);

        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }

    pid_t pid2 = fork();

    if (!pid2) {
        dup2(pfd[0], 0);

        close(pfd[0]);
        close(pfd[1]);

        execlp(argv[2], argv[2], NULL);
        _exit(1);
    }
    close(pfd[0]);
    close(pfd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
