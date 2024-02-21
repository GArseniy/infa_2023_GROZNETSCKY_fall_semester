#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int
parallel(char *exe, int *cnt)
{
    pid_t pid = fork();
    if (pid > 0) {
        return 0;
    }
    if (!pid) {
        execlp(exe, exe, NULL);
        _exit(1);
    }
    int st;
    while (wait(&st) != -1) {
        *cnt += WIFEXITED(st) && !WEXITSTATUS(st);
    }
    return 1;
}

int
step_by_step(char *exe, int *cnt)
{
    int st;
    while (wait(&st) != -1) {
        *cnt += WIFEXITED(st) && !WEXITSTATUS(st);
    }
    pid_t pid = fork();
    if (pid > 0) {
        wait(&st);
        *cnt += WIFEXITED(st) && !WEXITSTATUS(st);
        return 0;
    }
    if (!pid) {
        execlp(exe, exe, NULL);
        _exit(1);
    }
    return 1;
}

int
main(int argc, char **argv)
{
    int cnt = 0;
    for (int i = 1; i < argc; ++i) {
        if ((argv[i][0] == 'p' && parallel(argv[i] + 1, &cnt)) ||
            (argv[i][0] == 's' && step_by_step(argv[i] + 1, &cnt))) {
            return 1;
        }
    }
    int st;
    while (wait(&st) != -1) {
        if (WIFEXITED(st) && !WEXITSTATUS(st)) {
            ++cnt;
        }
    }
    printf("%d\n", cnt);
    return 0;
}