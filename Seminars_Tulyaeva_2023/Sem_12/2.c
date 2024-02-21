#include <signal.h>
#include <unistd.h>

// kill (0, ...) for user group
// kill (-1, ...) for all

volatile int cnt = 0;

void
handler(int sig)
{
    ++cnt;
    if (cnt == 4) {
        signal(sig, SIG_DFL);
    }
}

int
main(int argc, char **argv)
{
    signal(SIGINT, handler);
    for (;;) {
        pause();
    }
}