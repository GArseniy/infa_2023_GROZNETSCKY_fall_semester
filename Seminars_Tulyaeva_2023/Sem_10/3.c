#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

enum
{
    STR_LEN = 7
};

int
main(int argc, char **argv)
{
    for (int i = 1; i <= 3; ++i) {
        pid_t pid = fork();
        if (!pid) {
            char str[STR_LEN];
            setbuf(stdin, 0); // Или же read(), который не буферизует ввод
            fgets(str, STR_LEN, stdin);

            char **ptr = NULL;
            int n = (int) strtol(str, ptr, 10);

            printf("%d %d\n", n * n, i);
            exit(0);
        }
    }

    while (wait(NULL) != -1) {
    }

    return 0;
}