#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            printf("%d\n", i);
            fflush(stdout);
            return 0;
        } else {
            printf("%d ", i);
            fflush(stdout);
        }
        
        pid_t pid;
        if ((pid = fork()) > 0) {
            wait(NULL);
            return 0;
        } else if (pid < 0) {
            _exit(1);
        }
    }
    
    return 0;
}
