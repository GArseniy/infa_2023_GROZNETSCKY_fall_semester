#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    int pfd[2];
    pipe(pfd);

    pid_t pid_c1 = fork();

    if (!pid_c1) { // C1
        close(pfd[1]);

        pid_t pid_v1 = fork();
        if (!pid_v1) { // V1
            wait(NULL);

            int p;
            read(pfd[0], &p, sizeof(p));
            printf("V1: %d\n", p);
        }

        _exit(1);
    }

    pid_t pid_c2 = fork();

    if (!pid_c2) { // C2
        close(pfd[0]);
        close(pfd[1]);
        pid_t p = 0; // FIXME: get pid
        write(pfd[1], &p, sizeof(p));
        printf("V2: %d\n", pid_c1);
        _exit(1);
    }

    close(pfd[0]);
    close(pfd[1]);

    waitpid(pid_c1, NULL, 0);
    waitpid(pid_c2, NULL, 0);

    return 0;
}
