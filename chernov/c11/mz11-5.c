#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    int n;
    pid_t pid;

    if ((pid = fork()) == 0) {
        while (scanf("%d", &n) == 1) {
            pid_t pid;
            if ((pid = fork()) > 0) {
                int status;
                wait(&status);
                if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                    printf("%d\n", n);
                    fflush(stdout);
                } else {
                    
                    _exit(1);
                }

                _exit(0);
            } else if (pid < 0) {
                printf("-1\n");
                fflush(stdout);
                _exit(1);
            }
        }
    } else {
        wait(NULL);
    }
    
    return 0;
}
