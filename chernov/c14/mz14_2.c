#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// 0 - сложение, 1 - умножение
volatile int mode = 0; 

void hndlr_sigint(int s) {
    mode = 0;
}

void hndlr_sigquit(int s) {
    mode = 1;
}

int main(void) {
    sigaction(SIGINT, &(struct sigaction) {\
                            .sa_handler = hndlr_sigint,\
                            .sa_flags = SA_RESTART
                        }, NULL);

    sigaction(SIGQUIT, &(struct sigaction) {\
                            .sa_handler = hndlr_sigquit,\
                            .sa_flags = SA_RESTART
                        }, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    int n = 0;
    int res = 0;

    while (scanf("%d", &n) == 1) {
        if (mode == 0) {
            __builtin_add_overflow(res, n, &res);
        }

        if (mode == 1) {
            __builtin_mul_overflow(res, n, &res);
        }

        printf("%d\n", res);
        fflush(stdout);
    }
    
    return 0;
}
