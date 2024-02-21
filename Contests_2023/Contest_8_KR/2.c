#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

enum
{
    BASE = 17,
    SIZE_OF_MEM = 256
};

int
wrap_strtoull(char *str, unsigned long long *x)
{
    if (!str) {
        return -1;
    }
    errno = 0;
    char *p = NULL;
    *x = strtoull(str, &p, BASE);

    return -(errno || *p || p == str);
}

int
cmp(const void *x1, const void *x2)
{
    unsigned long long v1 = *(unsigned long long *) x1;
    unsigned long long v2 = *(unsigned long long *) x2;

    return (v1 > v2) ? 1 : ((v1 == v2) ? 0 : -1);
}

int
main(int argc, char **argv)
{
    unsigned long long *num = calloc(SIZE_OF_MEM, sizeof(*num));

    for (int num_size = SIZE_OF_MEM; num_size < argc; num_size += SIZE_OF_MEM) {
        num = realloc(num, (num_size + SIZE_OF_MEM) * sizeof(*num));
    }

    int len = 0;
    for (int i = 1; i < argc; ++i) {
        if (!wrap_strtoull(argv[i], &num[len])) {
            ++len;
        }
    }

    qsort(num, len, sizeof(*num), cmp);

    for (int i = 0; i < len; ++i) {
        printf("%llu\n", num[i]);
    }

    free(num);
    return 0;
}
