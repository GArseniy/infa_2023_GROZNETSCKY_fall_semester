#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

volatile int cur = 0, cnt = 0;

void hndlr_sigterm(int s) {
    _exit(0);
}

void hndlr_sigint(int s) {
    cnt++;

    if (cnt == 4) {
        _exit(0);
    }

    printf("%d\n", cur);
    fflush(stdout);
}

int is_prime(int x) {
    for (int i = 2; i < (int) sqrt(x) + 1; i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    
    return 1;
}

int main(void) {
    sigaction(SIGINT, &(struct sigaction) {\
                            .sa_handler = hndlr_sigint,\
                            .sa_flags = SA_RESTART
                        }, NULL);

    sigaction(SIGTERM, &(struct sigaction) {\
                            .sa_handler = hndlr_sigterm,\
                            .sa_flags = SA_RESTART
                        }, NULL);

    int low, high;
    if (scanf("%d %d", &low, &high) != 2) {
        return -1;
    }
    
    printf("%d\n", getpid());
    fflush(stdout);
    
    for (int i = low; i < high; i++) {
        if (is_prime(i)) {
            cur = i;
        }
    }
    
    printf("-1\n");
    fflush(stdout);
    
    return 0;
}
