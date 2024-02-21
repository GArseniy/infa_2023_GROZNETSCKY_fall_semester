#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
    int pfd[2];
    pipe(pfd);

    if (!fork()) {
        close(pfd[0]);
        dup2(pfd[1], 1);
        if (!fork()) {
            int fd_in = open(argv[3], O_RDONLY | O_CLOEXEC);
            dup2(fd_in, 0);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }

        int st;
        wait(&st);
        if (WIFEXITED(st) && !WEXITSTATUS(st)) {
            if (!fork()) {
                execlp(argv[5], argv[5], NULL);
                _exit(1);
            }
            _exit(0);
        }
        _exit(1);
    }

    if (!fork()) {
        close(pfd[1]);
        dup2(pfd[0], 0);
        int fd_out = open(argv[9], O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0777);
        dup2(fd_out, 1);
        execlp(argv[7], argv[7], NULL);
        _exit(1);
    }

    int st;
    while (wait(&st) != -1) {
    }

    return 0;
}
