#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>
#include <errno.h>

enum
{
    BASE = 10
};

void pong(FILE* fd_wr, FILE* fd_rd, int n, int pid) {
    int k;

    while (fscanf(fd_rd, "%d", &k) != -1) {
        printf("%d %d\n", pid, k);
        fflush(stdout);
    
        if (k == n) {
            _exit(0);
        }
        
        k++;
        fprintf(fd_wr, "%d\n", k);
        fflush(fd_wr);
    }
    _exit(0);
}

int main(int argc, char **argv) {
    char *eptr;
    errno = 0;
    int n = strtol(argv[1], &eptr, BASE);
    if (errno || *eptr || eptr == argv[1] || (int) n != n) {
        return -1;
    }
    
    n--;
    if (n == 0) {
        printf("Done\n");
        return 0;
    }
    
    pid_t pid;
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    if ((pid = fork()) == 0) {
        close(pipe1[1]);
        close(pipe2[0]);

        pong(fdopen(pipe2[1], "w"), fdopen(pipe1[0], "r"), n, 1);
    }
    if (pid < 0) {
        return 1;
    }
    
    if ((pid = fork()) == 0) {
        close(pipe1[0]);
        close(pipe2[1]);

        pong(fdopen(pipe1[1], "w"), fdopen(pipe2[0], "r"), n, 2);
    }

    dprintf(pipe1[1], "1\n");
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
    while (wait(NULL) != -1) {}
    
    printf("Done\n");
    fflush(stdout);
    
    return 0;
}
