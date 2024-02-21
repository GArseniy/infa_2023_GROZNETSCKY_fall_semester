#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

volatile int mode = 0;

void
handler(int s)
{
    if (s == SIGINT) {
        mode = 0;
    }
    if (s == SIGQUIT) {
        mode = 1;
    }
}

int
main(void)
{
    sigaction(SIGINT, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGQUIT, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int sum = 0;
    int x;
    while (scanf("%d", &x) == 1) {
        if (mode == 0) {
            __builtin_add_overflow(sum, x, &sum);
        }
        if (mode == 1) {
            __builtin_mul_overflow(sum, x, &sum);
        }
        printf("%d\n", sum);
        fflush(stdout);
    }
    return 0;
}