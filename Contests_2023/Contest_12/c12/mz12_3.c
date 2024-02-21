#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int res = 0, status;
    pid_t pid;
    for (int i = 1; i < argc; i++) {
        switch (argv[i][0]) {
            case 'p':
                pid = fork();
                if (pid < 0) {
                    while (wait(&status) != -1) {
                        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                            res++;
                        }
                    }
                    return -1;
                }

                if (pid == 0) {
                    execlp(argv[i] + 1, argv[i] + 1, NULL);
                    _exit(1);
                }
                break;
            case 's':
                while (wait(&status) != -1) {
                    if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                        res++;
                    }
                }
                pid = fork();
                if (pid < 0) {
                    return -1;
                }
                if (pid == 0) {
                    execlp(argv[i] + 1, argv[i] + 1, NULL);
                    _exit(1);
                }

                wait(&status);
                if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                    res++;
                }
                break;
            default:
                break;
        }
    }

    while (wait(&status) != -1) {
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            res++;
        }
    }

    printf("%d\n", res);

    return 0;
}
