#include <signal.h>
#include <stdio.h>

volatile int mode = 0;

void
handler(int sig)
{
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    if (sig == SIGUSR1) {
        mode = 0;
    }
    if (sig == SIGUSR2) {
        mode = 1;
    }
}

int
main(int argc, char **argv)
{
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    int x;
    while (scanf("%d", &x) == 1) {
        printf("%d\n", mode ? x * x : -x);
    }

    return 0;
}