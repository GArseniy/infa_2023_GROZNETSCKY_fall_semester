#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main(void) {
    int fd[2];
    pipe(fd);
    pid_t pid;
    if ((pid = fork()) == 0) {
        if ((pid = fork()) == 0) {
            close(fd[0]);
            time_t cur_time = time(NULL);
            struct tm *mtm = localtime(&cur_time);
            printf("D:%02d\n", mtm->tm_mday);
            fflush(stdout);

            write(fd[1], &cur_time, sizeof(cur_time));
            write(fd[1], &cur_time, sizeof(cur_time));
            close(fd[1]);
    
            _exit(0);
        }
        
        if (pid < 0) {
            _exit(1);
        }

        time_t cur_time;
        read(fd[0], &cur_time, sizeof(cur_time));
        close(fd[0]);

        struct tm *mtm = localtime(&cur_time);
        printf("M:%02d\n", mtm->tm_mon + 1);
        fflush(stdout);

        _exit(0);
    }
    
    if (pid < 0) {
        return -1;
    }
    
    wait(NULL);
    
    close(fd[1]);
    time_t cur_time;
    read(fd[0], &cur_time, sizeof(cur_time));
    close(fd[0]);
    
    struct tm *mtm = localtime(&cur_time);
    printf("Y:%d\n", mtm->tm_year + 1900);
    fflush(stdout);
    
    return 0;
}
