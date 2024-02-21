#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

void
stride(int argc, char **argv)
{
    int cnt = 0;

    for (int i = 1; i < argc; ++i) {
        pid_t pid;
        if (!(pid = fork())) {
            execlp(argv[i], argv[i], NULL);
            exit(1);
        }
        int status;
        if (wait(&status) == -1) {
            continue;
        }

        if (!WIFEXITED(status) || WEXITSTATUS(status)) {
            ++cnt;
        }
    }

    printf("%d\n", cnt);
}

void
parallel(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        pid_t pid;
        if (!(pid = fork())) {
            execlp(argv[i], argv[i], NULL);
            exit(1);
        }
    }

    int cnt = 0;
    int status;
    while (wait(&status) != -1) {
        if (!WIFEXITED(status) || WEXITSTATUS(status)) {
            ++cnt;
        }
    }

    printf("%d\n", cnt);
}