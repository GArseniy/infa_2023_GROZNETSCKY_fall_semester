#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

int
main(void)
{
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        printf(i == n ? "%d\n" : "%d ", i);
        fflush(stdout);

        if (i != n) {
            pid_t pid = fork();
            if (pid < 0) {
                exit(1);
            }
            if (pid) {
                wait(NULL);
                exit(0);
            }
        }
    }

    return 0;
}