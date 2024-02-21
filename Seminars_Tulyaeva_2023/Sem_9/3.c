#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

int
main(void)
{
    int n = 3;

    for (int i = 1; i <= n; ++i) {
        printf("%d\n", i);
        fflush(stdout);

        if (i != n) {
            pid_t pid = fork();
            if (pid < 0) {
                exit(1);
            }
            if (pid) {
                int status;
                wait(&status);
                exit(0);
            }
        }
    }

    return 0;
}
