#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void
ping(int p_1, int p_2, int n)
{
    int x;
    while (read(p_1, &x, sizeof(x)) && x <= n) {
        printf("%d %d\n", getpid(), x);
        ++x;
        write(p_2, &x, sizeof(x));
    }
    exit(0);
}

int
main(int argc, char **argv)
{
    int n = strtol(argv[1], NULL, 10);

    int p_1[2];
    pipe(p_1);

    int p_2[2];
    pipe(p_2);

    int x = 1;
    write(p_1[1], &x, sizeof(x));

    pid_t pid1 = fork();
    if (!pid1) {
        close(p_1[1]);
        close(p_2[0]);
        proc(p_1[0], p_2[1], n);
    }

    pid_t pid2 = fork();
    if (!pid2) {
        close(p_1[0]);
        close(p_2[1]);
        proc(p_2[0], p_1[1], n);
    }

    close(p_1[0]);
    close(p_2[0]);

    close(p_1[1]);
    close(p_2[1]);

    return 0;
}
