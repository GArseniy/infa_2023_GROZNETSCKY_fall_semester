#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

enum
{
    STR_LEN = 8,
    STR_CNT = 3
};

int
main(void)
{
    for (int i = 1; i <= STR_CNT; ++i) {
        if (!fork()) {
            char str[STR_LEN];
            if (read(0, str, sizeof(str)) != sizeof(str)) {
                exit(1);
            }
            str[STR_LEN - 1] = 0;
            int n = (int) strtol(str, NULL, 10);
            printf("%d %d\n", i, n * n);
            fflush(stdout);
            exit(0);
        }
    }

    while (wait(NULL) != -1) {
    }

    return 0;
}