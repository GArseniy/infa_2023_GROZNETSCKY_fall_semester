#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>

enum
{
    BASE = 10
};

int main(int argc, char **argv) {
    int BASE = 10;

    char *eptr = NULL;
    errno = 0;
    long n = strtol(argv[1], &eptr, BASE);
    if (errno || *eptr || eptr == argv[1] || (int) n != n) {
        return -1;
    }
    
    int res = 0;
    
    for (int i = 2; i < argc && i - 2 < n; i++) {
        pid_t pid;
        if ((pid = fork()) == 0) {
            FILE *file = fopen(argv[i], "r");
            char path[PATH_MAX + 1];
            fgets(path, PATH_MAX, file);
            path[strlen(path) - 1] = '\0';
            
            execlp(path, path, NULL);
            _exit(1);
        }
    }
    
    int status;
    while (wait(&status) != -1) {
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            res++;
        }
    }
    
    for (int i = n + 2; i < argc; i++) {
        pid_t pid;
        if ((pid = fork()) == 0) {
            FILE *file = fopen(argv[i], "r");
            char path[PATH_MAX + 1];
            fgets(path, PATH_MAX, file);
            path[strlen(path) - 1] = '\0';
            
            execlp(path, path, NULL);
            _exit(1);
        }
        
        int status;
        wait(&status);
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            res++;
        }
    }

    printf("%d\n", res);
    fflush(stdout);
}
