#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int cnt = 0;

void
handler(int s)
{
    if (cnt == 5) {
        _exit(0);
    }

    printf("%d\n", cnt++);
    fflush(stdout);
}

int
main(int argc, char **argv)
{
    sigaction(SIGHUP, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    while (1) {
        pause();
    }
}