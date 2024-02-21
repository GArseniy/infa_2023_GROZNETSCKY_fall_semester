#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {
    int fd[2];
    pipe(fd);
    
    pid_t pid;
    if ((pid = fork()) == 0) {
        if (fork() == 0) {
            close(fd[1]);
            int cur;
            long long res = 0;
            while (read(fd[0], &cur, sizeof(cur)) == sizeof(cur)) {
                res += cur;
            }
            
            printf("%lld\n", res);
            fflush(stdout);
            _exit(1);
        }
        close(fd[1]);
        close(fd[0]);
        wait(NULL);
        _exit(0);
    }

    if (pid < 0) {
        return 1;
        
    }
    
    close(fd[0]);
    int n;
    while (scanf("%d", &n) != -1) {
        if (write(fd[1], &n, sizeof(n)) != sizeof(n)) {
            return 1;
        }
    }
    close(fd[1]);
    wait(NULL);
    return 0;
}
