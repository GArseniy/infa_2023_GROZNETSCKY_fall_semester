#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <signal.h>
#include <sys/signalfd.h>

void
handler(int s)
{
    
}

int
main(int argc, char *argv[])
{
    unsigned char c = 0;
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGUSR1);
    sigaddset(&s, SIGUSR2);
    sigaddset(&s, SIGALRM);
    sigaddset(&s, SIGIO);
    sigprocmask(SIG_BLOCK, &s, NULL);
    int p1 = fork();
    if (!p1) {
        int count = 0;
        struct signalfd_siginfo sinfo;
        sigset_t s;
        sigemptyset(&s);
        sigaddset(&s, SIGUSR1);
        sigaddset(&s, SIGUSR2);
        sigaddset(&s, SIGIO);
        int sfd = signalfd(-1, &s, 0);
        for (;;) {
            read(sfd, &sinfo, sizeof(sinfo));
            if (sinfo.ssi_signo == SIGUSR1) {
                count++;
                if (count == 8) {
                    printf("%c", c);
                    fflush(stdout);
                    c = 0;
                    count = 0;
                }
                kill(sinfo.ssi_pid, SIGALRM);
            } else if (sinfo.ssi_signo == SIGUSR2) {
                c |= (1 << count);
                count++;
                if (count == 8) {
                    printf("%c", c);
                    fflush(stdout);
                    c = 0;
                    count = 0;
                }
                kill(sinfo.ssi_pid, SIGALRM);
            } else if (sinfo.ssi_signo == SIGIO) {
                if (count) {
                    printf("%c", c);
                    fflush(stdout);
                }
                _exit(0);
            }
        }
    } else if (p1 == -1) {
        _exit(1);
    }
    int p2 = fork();
    if (!p2) {
        int file = open(argv[1], O_RDONLY);
        struct signalfd_siginfo sinfo;
        sigset_t s;
        sigemptyset(&s);
        sigaddset(&s, SIGALRM);
        sigaction(SIGALRM, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
        int sfd = signalfd(-1, &s, 0);
        while (read(file, &c, sizeof(c)) > 0) {
            for (int i = 0; i < 8; i++) {
                if (c % 2) {
                    kill(p1, SIGUSR2);
                } else {
                    kill(p1, SIGUSR1);
                }
                read(sfd, &sinfo, sizeof(sinfo));
                c >>= 1;
            }
        }
        kill(p1, SIGIO);
        _exit(0);
    } else if (p2 == -1) {
        _exit(1);
    }
    while(wait(NULL) > 0);
    _exit(0);
}