#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int
main()
{
    int fd[2];
    pipe(fd);
    if (!fork()) {
        close(fd[1]);
        if (!fork()) {
            long long sum = 0;
            int buf;
            while (read(fd[0], &buf, sizeof(buf)) > 0) {
                sum += buf;
            }
            printf("%lld\n", sum);
        }
        close(fd[0]);
    } else {
        close(fd[0]);
        int buf;
        while (scanf("%d", &buf) == 1) {
            write(fd[0], &buf, sizeof(buf));
        }
        close(fd[1]);
    }
    while (wait(NULL) != -1) {
    }
    return 0;
}