#include <stdio.h>
#include <time.h>

enum
{
    FIRST_YEAR = 1900,
};

void
f(int *y, int *m, int *d, int offset)
{
    struct tm t = {};

    t.tm_year = *y - FIRST_YEAR;
    t.tm_mon = *m - 1;
    t.tm_mday = *d + offset;
    t.tm_isdst = -1;

    mktime(&t);

    *y = t.tm_year + FIRST_YEAR;
    *m = t.tm_mon + 1;
    *d = t.tm_mday;
}

int
main(int argc, char **argv)
{
    int d = 25, m = 5, y = 2004; // 25.05.2004
    f(&y, &m, &d, 10);
    printf("%d %d %d\n", d, m, y);

    return 0;
}
