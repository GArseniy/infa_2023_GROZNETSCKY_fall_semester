#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    char **ptr = NULL;
    int n = strtol(argv[1], ptr, 10);

    for (int i = 1; i <= n; ++i) {
        if (i != n) {
            pid_t pid = fork();
            if (pid < 0) {
                exit(1);
            }
            if (pid) {
                int status;
                wait(&status);
                printf("%d\n", i);
                fflush(stdout);
                exit(0);
            }
        } else {
            printf("%d\n", i);
            fflush(stdout);
        }
    }

    return 0;
}
