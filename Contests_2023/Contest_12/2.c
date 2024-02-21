#include <unistd.h>
#include <wait.h>

int
run(const char *exe)
{
    pid_t pid = fork();
    if (pid < 0) {
        return 0;
    }
    if (pid > 0) {
        int st;
        wait(&st);
        return WIFEXITED(st) && !WEXITSTATUS(st);
    }
    execlp(exe, exe, NULL);
    _exit(1);
}

int
main(int argc, char **argv)
{
    return !((run(argv[1]) || run(argv[2])) && run(argv[3]));
}