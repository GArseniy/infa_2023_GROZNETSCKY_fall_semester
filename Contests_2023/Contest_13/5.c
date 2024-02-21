#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

void
ping(int stdout_fd, int id, int n)
{
    int x;
    while (scanf("%d", &x) == 1) {
        dprintf(stdout_fd, "%d %d\n", id, x);
        if (++x >= n) {
            break;
        }
        printf("%d\n", x);
        fflush(stdout);
    }
    _exit(0);
}

enum
{
    ID_1 = 1,
    ID_2 = 2
};

int
main(int argc, char **argv)
{
    int n = strtol(argv[1], NULL, 10);

    if (n <= 1) {
        printf("Done\n");
        return 0;
    }

    int p_1[2];
    pipe(p_1);

    int p_2[2];
    pipe(p_2);

    dprintf(p_1[1], "1\n");

    int stdout_fd = dup(1);

    if (!fork()) {
        close(p_1[1]);
        close(p_2[0]);
        dup2(p_1[0], 0);
        dup2(p_2[1], 1);

        ping(stdout_fd, ID_1, n);
    }

    if (!fork()) {
        close(p_1[0]);
        close(p_2[1]);
        dup2(p_2[0], 0);
        dup2(p_1[1], 1);

        ping(stdout_fd, ID_2, n);
    }

    close(p_1[0]);
    close(p_2[0]);

    close(p_1[1]);
    close(p_2[1]);

    while (wait(NULL) != -1) {
    }
    printf("Done\n");
    fflush(stdout);

    return 0;
}