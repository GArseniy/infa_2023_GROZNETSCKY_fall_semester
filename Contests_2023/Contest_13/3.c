#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int
main(int argc, char **argv)
{
    int pfd[2];
    pipe(pfd);

    if (!fork()) {
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);

        if (!fork()) {
            int fd_in = open(argv[4], O_RDONLY | O_CLOEXEC);
            dup2(fd_in, 0);
            close(fd_in);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }

        int status;
        wait(&status);
        if (!WIFEXITED(status) || WEXITSTATUS(status)) {
            _exit(0);
        }

        if (!fork()) {
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }

        wait(NULL);
        _exit(0);
    }

    if (!fork()) {
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);

        int fd_out = open(argv[5], O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0600);
        dup2(fd_out, 1);
        close(fd_out);

        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }

    close(pfd[0]);
    close(pfd[1]);

    while (wait(NULL) != -1) {
    }
    return 0;
}