#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

enum
{
    N = 3
};

int
main(void)
{
    for (int i = 1; i <= N; ++i) {
        if (i != N) {
            pid_t pid = fork();
            if (pid < 0) {
                exit(1);
            }
            if (pid) {
                wait(NULL);

                printf(i == 1 ? "%d\n" : "%d ", i);
                fflush(stdout);

                exit(0);
            }
        } else {
            printf("%d ", i);
            fflush(stdout);
        }
    }

    return 0;
}
