#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

char *
wrap_strtol(char *str, int *x)
{
    if (!str) {
        return NULL;
    }
    errno = 0;
    char *p = NULL;
    long n = strtol(str, &p, 10);
    if (errno || p == str || (int) n != n) {
        errno = 0;
        return NULL;
    }
    *x = n;
    return p;
}

int
main(int argc, char **argv)
{
    long long res = 0;

    for (int i = 1; i < argc; i++) {
        int x;
        char *p;
        if (!(p = wrap_strtol(argv[i], &x))) {
            continue;
        }

        long long upd_x = x;
        if (*p == 'k') {
            if (__builtin_mul_overflow(x, 1000, &upd_x)) { // upd_x *= 1000;
                continue;
            }
            ++p;
        }
        res += upd_x * (!strcmp(p, "+") - !strcmp(p, "-"));
    }
    printf("%lld\n", res);

    return 0;
}
