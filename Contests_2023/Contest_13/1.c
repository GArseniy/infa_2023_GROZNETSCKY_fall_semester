#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdio.h>

enum
{
    YEAR = 1900,
    MONTH = 1,

    CNT_PROS = 3
};

int
main(void)
{
    int pfd[2];
    pipe(pfd);

    if (fork()) {
        close(pfd[1]);
        wait(NULL);

        time_t buf;
        read(pfd[0], &buf, sizeof(buf));
        close(pfd[0]);

        struct tm *data = localtime(&buf);
        printf("Y:%.4d\n", data->tm_year + YEAR);
        fflush(stdout);

        _exit(0);
    }

    if (fork()) {
        close(pfd[1]);
        wait(NULL);

        time_t buf;
        read(pfd[0], &buf, sizeof(buf));
        close(pfd[0]);

        struct tm *data = localtime(&buf);
        printf("M:%.2d\n", data->tm_mon + MONTH);
        fflush(stdout);

        _exit(0);
    }

    time_t t = time(NULL);
    for (int i = 0; i < CNT_PROS; ++i) {
        write(pfd[1], &t, sizeof(t));
    }
    close(pfd[1]);

    time_t buf;
    read(pfd[0], &buf, sizeof(buf));
    close(pfd[0]);

    struct tm *data = localtime(&buf);
    printf("D:%.2d\n", data->tm_mday);
    fflush(stdout);

    _exit(0);
}