#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <sys/file.h>

enum
{
    ERR = 42
};

int
main(int argc, char **argv)
{
    if (fork()) {
        int status;
        wait(&status);
        printf("%d\n", status);
        return 0;
    }

    int fd_in = open(argv[2], O_RDONLY | O_CLOEXEC);
    int fd_out = open(argv[3], O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0660);
    int fd_err = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0660);

    if (fd_in == -1 || dup2(fd_in, 0) == -1) {
        _exit(ERR);
    }
    if (fd_out == -1 || dup2(fd_out, 1) == -1) {
        _exit(ERR);
    }
    if (fd_err == -1 || dup2(fd_err, 2) == -1) {
        _exit(ERR);
    }

    execlp(argv[1], argv[1], NULL);

    close(fd_in);
    close(fd_out);
    close(fd_err);

    _exit(ERR);
}