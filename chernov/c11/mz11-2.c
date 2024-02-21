#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

enum
{
    SON_NUM = 3
};

int main(void) {
    for (int i = 1; i <= SON_NUM; i++) {
        pid_t pid;
        if (i != SON_NUM && (pid = fork()) > 0) {
            wait(NULL);
            if (i != 1) {
                printf("%d ", i);
                fflush(stdout);
            } else {
                printf("%d\n", i);
                fflush(stdout);
            }

            return 0;
        } else if (i == SON_NUM) {
            printf("%d ", i);
            fflush(stdout);
        }
    }

    return 0;
}
