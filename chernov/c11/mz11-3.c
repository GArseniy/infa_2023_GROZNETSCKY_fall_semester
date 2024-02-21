#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

enum
{
    SON_NUM = 3,
    BASE = 10,
    STR_SIZE = 8
};

int main(void) {
    for (int i = 1; i <= SON_NUM; i++) {
        if (fork() == 0) {
            char buf[STR_SIZE];
            if (read(0, buf, sizeof(buf)) != sizeof(buf)) {
                _exit(1);
            }
    
            buf[STR_SIZE - 1] = '\0';

            int x = strtol(buf, 0, BASE);

            printf("%d %d\n", i, x * x);
            fflush(stdout);
            _exit(0);
        }
    }
    
    while (wait(NULL) != - 1) {}

    return 0;
}
