#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>

int execute(char *path) {
    pid_t pid = fork();
    if (pid < 0) {
        return 0;
    } else if (pid == 0) {
        execlp(path, path, NULL);
        _exit(1);
    }

    int status;
    wait(&status);
    return WIFEXITED(status) && !WEXITSTATUS(status);
}

int main(int argc, char **argv) {
    return !((execute(argv[1]) || execute(argv[2])) && execute(argv[3]));
}
