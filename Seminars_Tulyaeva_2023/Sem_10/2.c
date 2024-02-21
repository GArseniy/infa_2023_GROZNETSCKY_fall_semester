#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

int
run(const char *exe)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        exit(1);
    }

    if (!pid) {
        execlp(exe, exe, NULL);
        exit(1);
    }

    int st;
    wait(&st);
    return WIFEXITED(st) && !WEXITSTATUS(st);
}

int
main(int argc, char **argv)
{

    return !((run(argv[1]) || run(argv[2])) && run(argv[3]));
}
