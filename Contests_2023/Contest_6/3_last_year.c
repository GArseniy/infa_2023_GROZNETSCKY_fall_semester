#include <stdio.h>
#include <time.h>
#include <errno.h>

enum
{
    MAX_DAY = 31,
    MAX_MONTH = 12,
    FIRST_YEAR = 1900,
    MIN_YEAR = 1910,
    MAX_YEAR = 2037,
    THU = 4
};

int
main(int argc, char **argv)
{
    int year;
    if (scanf("%d", &year) != 1 || year > MAX_YEAR || year < MIN_YEAR) {
        return 1;
    }

    struct tm t = {};
    for (int m = 0; m < MAX_MONTH; ++m) {
        int cnt_thu = 0;
        for (int d = 1; d <= MAX_DAY; ++d) {
            t.tm_year = year - FIRST_YEAR;
            t.tm_mon = m;
            t.tm_mday = d;
            t.tm_isdst = -1;

            if ((errno = 0, mktime(&t) == -1) && errno) {
                continue;
            }

            if (m == t.tm_mon && t.tm_wday == THU && !(++cnt_thu % 2) && (d % 3)) {
                printf("%d %d\n", m + 1, d);
            }
        }
    }

    return 0;
}
