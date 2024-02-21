#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <wait.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    long long multiple = strtoll(argv[1], NULL, 10);

    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGUSR1);
    sigprocmask(SIG_BLOCK, &s, NULL);

    int pfd[2];
    pipe(pfd);

    pid_t son;
    if (!(son = fork())) {
        pid_t father = getppid();
        pid_t grand_son;
        if (!(grand_son = fork())) {
            sigset_t s2;
            sigemptyset(&s2);
            sigaddset(&s2, SIGUSR1);
            int sfd2 = signalfd(-1, &s2, 0);
            struct signalfd_siginfo s_info;

            int end = 0;

            long long n;
            while (!end) {
                read(sfd2, &s_info, sizeof(s_info));

                printf("GRAND SON %lld\n", n); // FIXME
                fflush(stdout);

                if (s_info.ssi_signo == SIGUSR1) {

                    if (s_info.ssi_pid == son) {

                        read(pfd[0], &n, sizeof(n));
                        printf("%lld\n", n);
                        fflush(stdout);

                        printf("GRAND SON1  %lld\n", n); // FIXME
                        fflush(stdout);

                        n *= multiple;
                        write(pfd[1], &n, sizeof(n));
                        kill(father, SIGUSR1);
                    } else {
                        printf("GRAND SON2\n"); // FIXME
                        fflush(stdout);
                        end = 1;
                    }
                }
            }
            close(sfd2);
            close(pfd[0]);
            close(pfd[1]);

            printf("GRAND SON2 BYE\n"); // FIXME
            fflush(stdout);
            _exit(0);
        }

        close(pfd[0]);

        sigset_t s1;
        sigemptyset(&s1);
        sigaddset(&s1, SIGUSR1);
        int sfd1 = signalfd(-1, &s1, 0);
        struct signalfd_siginfo s_info;

        long long n;
        while (scanf("%lld", &n) == 1) {
            printf("Hello %lld\n", n); // FIXME
            fflush(stdout);
            read(sfd1, &s_info, sizeof(s_info));

            if (s_info.ssi_signo == SIGUSR1) {
                write(pfd[1], &n, sizeof(n));
                kill(grand_son, SIGUSR1);
            }
        }

        write(pfd[1], &grand_son, sizeof(grand_son));

        close(sfd1);
        close(pfd[1]);
        kill(getppid(), SIGUSR1);
        printf("Bye\n"); // FIXME
        fflush(stdout);
        wait(NULL);
        _exit(0);
    }

    close(pfd[1]);

    sigset_t s0;
    sigemptyset(&s0);
    sigaddset(&s0, SIGUSR1);
    int sfd0 = signalfd(-1, &s0, 0);
    struct signalfd_siginfo s_info;

    int end = 0;
    pid_t grand_son;
    long long n;

    printf("Hello FATHER\n"); // FIXME
    fflush(stdout);

    kill(son, SIGUSR1);
    while (!end) {
        read(sfd0, &s_info, sizeof(s_info));

        printf("Hello FATHER 1\n"); // FIXME
        fflush(stdout);

        if (s_info.ssi_signo == SIGUSR1) {
            if (s_info.ssi_pid == son) {
                printf("Bye FATHER 1\n"); // FIXME
                fflush(stdout);
                read(pfd[0], &grand_son, sizeof(grand_son));
                end = 1;
            } else {
                read(pfd[0], &n, sizeof(n));
                printf("%lld\n", n);
                fflush(stdout);

                printf("Bye FATHER 2 %lld\n", n); // FIXME
                fflush(stdout);

                kill(son, SIGUSR1);
            }
        }
    }

    close(pfd[0]);
    close(sfd0);

    printf("Bye FATHER END\n"); // FIXME
    fflush(stdout);

    kill(grand_son, SIGUSR1);

    wait(NULL);
    return 0;
}