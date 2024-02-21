#include <sys/signalfd.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <wait.h>

int
main(int argc, char **argv)
{
    sigset_t s0;
    sigemptyset(&s0);
    sigaddset(&s0, SIGUSR1);
    sigaddset(&s0, SIGUSR2);
    sigaddset(&s0, SIGIO);
    sigaddset(&s0, SIGALRM);
    sigprocmask(SIG_BLOCK, &s0, NULL);

    pid_t son_1;
    if (!(son_1 = fork())) {
        sigset_t s1;
        sigemptyset(&s1);
        sigaddset(&s1, SIGUSR1);
        sigaddset(&s1, SIGUSR2);
        sigaddset(&s1, SIGIO);
        int sfd = signalfd(-1, &s1, 0);
        struct signalfd_siginfo s_info;

        int bit_num = CHAR_BIT;
        char buffer = 0;
        int end = 0;

        while (!end) {
            read(sfd, &s_info, sizeof(s_info));

            if (s_info.ssi_signo == SIGIO) {
                end = 1;
            } else if (s_info.ssi_signo == SIGUSR1 || s_info.ssi_signo == SIGUSR2) {
                buffer |= (s_info.ssi_signo == SIGUSR2) << --bit_num;
                if (!bit_num) {
                    printf("%c", buffer);
                    fflush(stdout);
                    bit_num = CHAR_BIT;
                    buffer = 0;
                }
                kill(s_info.ssi_pid, SIGALRM);
            }
        }

        close(sfd);
        _exit(0);
    }

    if (!fork()) {
        sigset_t s2;
        sigemptyset(&s2);
        sigaddset(&s2, SIGALRM);
        int sfd = signalfd(-1, &s2, 0);
        struct signalfd_siginfo s_info;

        int fd = open(argv[1], O_RDONLY);

        char buf;
        while (read(fd, &buf, sizeof(buf)) == sizeof(buf)) {
            for (int j = CHAR_BIT - 1; j >= 0; --j) {
                kill(son_1, buf & (1u << j) ? SIGUSR2 : SIGUSR1);
                read(sfd, &s_info, sizeof(s_info));
            }
        }

        kill(son_1, SIGIO);
        close(sfd);
        close(fd);
        _exit(0);
    }

    while (wait(NULL) != -1) {
    }

    return 0;
}