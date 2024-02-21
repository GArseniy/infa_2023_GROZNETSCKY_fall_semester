#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int
main(void)
{
    int pfd[2];
    pipe(pfd);

    if (fork()) {
        close(pfd[0]);
        int x;
        while (scanf("%d", &x) == 1) {
            write(pfd[1], &x, sizeof(x));
        }
        close(pfd[1]);
        wait(NULL);
        _exit(0);
    }

    if (fork()) {
        close(pfd[0]);
        close(pfd[1]);
        wait(NULL);
        _exit(0);
    }

    close(pfd[1]);

    long long sum = 0;
    int x;
    while (read(pfd[0], &x, sizeof(x)) > 0) {
        sum += x;
    }
    printf("%lld", sum);
    fflush(stdout);

    close(pfd[0]);
    _exit(0);
}