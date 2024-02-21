#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>
#include <errno.h>

<<<<<<< HEAD
int cnt = 0;
pid_t *pid;
=======
void kill_all(pid_t *pid, int n) {
    for (int i = 0; i < n; i++) {
        kill(pid[i], SIGKILL);
    }
}

int main(int argc, char **argv) {
    pid_t pid[argc];
    int prev = 0;
    dup2(0, prev);
>>>>>>> d57e1ad183a87c138fa39d3f19c29490c147b6ba

void kill_all() {
    for (int i = 0; i < cnt - 1; i++) {
        if (pid[i] != 0) {
            kill(pid[i], SIGKILL);
        }
    }

    while (wait(NULL) != -1) {}
}

void SigHndlr(int sig) {
    kill_all();
    free(pid);
    _exit(1);
}

int main(int argc, char **argv) {
    signal(SIGUSR1, SigHndlr);

    pid = calloc(argc, sizeof(*pid));

    int prev = 0;

    for (cnt = 1; cnt < argc; cnt++) {
        int fd[2];
        if (pipe(fd) != 0) {
<<<<<<< HEAD
            cnt--;
            kill_all();
            free(pid);
=======
            kill_all(pid, i - 2);
>>>>>>> d57e1ad183a87c138fa39d3f19c29490c147b6ba
            return 1;
        }

        if ((pid[cnt - 1] = fork()) == 0) {
            free(pid);
            close(fd[0]);

            if (cnt != 1) {
                if (dup2(prev, 0) < 0) {
                    kill(getppid(), SIGUSR1);
                    return 1;
                }
            }

            if (prev) {
                close(prev);
            }

            if (cnt != argc - 1) {
                if (dup2(fd[1], 1) < 0) {
                    kill(getppid(), SIGUSR1);
                    free(pid);
                    return 1;
                }
            }

            close(fd[1]);

            execlp(argv[cnt], argv[cnt], NULL);

            kill(getppid(), SIGUSR1);
            _exit(1);
        }

        if (pid[cnt - 1] < 0) {
            kill_all();
            return 1;
        }

        if (prev) {
            close(prev);
        }

        prev = fd[0];
        close(fd[1]);
<<<<<<< HEAD
=======

        if (pid[i - 1] < 0) {
            kill_all(pid, i - 2);

            return 1;
        }
>>>>>>> d57e1ad183a87c138fa39d3f19c29490c147b6ba
    }

    while(wait(NULL) != -1) {}
    
    free(pid);
    return 0;
}
