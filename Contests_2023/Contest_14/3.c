#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>

void
exec(char *f_name)
{
    FILE *file = fopen(f_name, "r");
    if (file == NULL) {
        _exit(1);
    }
    char path[PATH_MAX];
    fgets(path, PATH_MAX, file);
    path[strlen(path) - 1] = '\0';

    execlp(path, path, NULL);
    _exit(1);
}

int
main(int argc, char **argv)
{
    int n = strtol(argv[1], NULL, 0);
    int cnt = n > (argc - 2) ? (argc - 2) : n;

    for (int i = 0; i < cnt; ++i) {
        if (!fork()) {
            exec(argv[i + 2]);
        }
    }

    int res = 0;
    int status;
    while (wait(&status) != -1) {
        res += WIFEXITED(status) && !WEXITSTATUS(status);
    }

    for (int i = n; i < argc - 2; ++i) {
        if (!fork()) {
            exec(argv[i + 2]);
        }

        wait(&status);
        res += WIFEXITED(status) && !WEXITSTATUS(status);
    }

    printf("%d\n", res);
    return 0;
}