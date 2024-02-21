#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int cnt = 0;

void handler(int s) {
    if (cnt == 5) {
        _exit(0);    
    }

    printf("%d\n", cnt);
    fflush(stdout);
    cnt++;   
}

int main(void) {
    sigaction(SIGHUP, &(struct sigaction) {\
                            .sa_handler = hndlr,\
                            .sa_flags = SA_RESTART
                        }, NULL);
    
    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);
    
    while (1) {
        pause();
    }
}
