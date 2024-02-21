#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

enum
{
    BASE = 8
};

int
wrap_strtol(char *str, mode_t *x)
{
    if (!str) {
        return -1;
    }
    errno = 0;
    char *p = NULL;
    long n = strtol(str, &p, BASE);
    if (errno || *p || p == str || (int) n != n) {
        errno = 0;
        return -1;
    }
    *x = n;
    return 0;
}

int
main(int argc, char **argv)
{
    const char temp[] = "rwxrwxrwx";
    enum
    {
        SIZE_OF_ROOTS = sizeof(temp) - 1,
        MIN_ROOTS = 0,
        MAX_ROOTS = ~0u >> (sizeof(int) * CHAR_BIT - SIZE_OF_ROOTS)
    };

    char mode[SIZE_OF_ROOTS + 1];
    mode[SIZE_OF_ROOTS] = 0;

    for (int i = 1; i < argc; ++i) {
        mode_t m;
        if (wrap_strtol(argv[i], &m) || m > MAX_ROOTS || m < MIN_ROOTS) {
            continue;
        }

        for (int j = 0; j < SIZE_OF_ROOTS; ++j, m >>= 1) {
            mode[SIZE_OF_ROOTS - 1 - j] = (m & 1) ? temp[SIZE_OF_ROOTS - 1 - j] : '-';
        }
        printf("%s\n", mode);
    }

    return 0;
}