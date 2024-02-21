#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int cnt = 0;
volatile int prime = 0;

enum
{
    CNT_MAX = 4
};

int
is_prime(int x)
{
    if (x <= 1) {
        return 0;
    }

    for (int i = 2; i * i < x; ++i) {
        if (x % i == 0) {
            return 0;
        }
    }

    return 1;
}

void
handler(int s)
{
    if (s == SIGINT) {
        if (++cnt == CNT_MAX) {
            _exit(0);
        }

        printf("%d\n", prime);
        fflush(stdout);
    }
    if (s == SIGTERM) {
        _exit(0);
    }
}

int
main(void)
{
    sigaction(SIGINT, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGTERM, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int low, high;
    scanf("%d %d", &low, &high);

    for (int i = low; i < high; ++i) {
        if (is_prime(i)) {
            prime = i;
        }
    }

    printf("-1\n");
    fflush(stdout);

    return 0;
}