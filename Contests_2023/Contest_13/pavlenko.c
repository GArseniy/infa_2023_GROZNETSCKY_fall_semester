#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(void)
{
    struct tm tmstr = {};
    int fds[2];
    pipe(fds);

    pid_t p1 = fork();
    if (!p1) {
        pid_t p2 = fork();
        if (!p2) {
            pid_t pid3 = fork();
            if (!pid3) {
                time_t cur_time;
                time(&cur_time);
                for (int i = 0; i < 3; ++i) {
                    write(fds[1], &cur_time, sizeof(cur_time));
                }
            } else {
                wait(NULL);
                time_t cur_time;
                read(fds[0], &cur_time, sizeof(cur_time));
                gmtime_r(&cur_time, &tmstr);
                printf("D:%2d\n", tmstr.tm_mday);
            }
        } else {
            wait(NULL);
            time_t cur_time;
            read(fds[0], &cur_time, sizeof(cur_time));
            gmtime_r(&cur_time, &tmstr);
            printf("M:%2d\n", tmstr.tm_mon + 1);
        }
    } else {
        wait(NULL);
        time_t cur_time;
        read(fds[0], &cur_time, sizeof(cur_time));
        gmtime_r(&cur_time, &tmstr);
        printf("Y:%4d\n", tmstr.tm_year + 1900);
    }
    close(fds[0]);
    close(fds[1]);
}