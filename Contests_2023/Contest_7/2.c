#include <stdio.h>
#include <time.h>
#include <string.h>

enum
{
    MAX_DAY = 31,
    MAX_MONTH = 12,

    FIRST_YEAR = 1900,
    MIN_YEAR = 1910,
    MAX_YEAR = 2037,

    WEEK = 7,
    THU = 4,

    MULTIPLE_WEEK = 2,
    MULTIPLE_DAY = 3
};

void
init_tm(struct tm *t, int year, int month, int day)
{
    memset(t, 0, sizeof(*t));
    t->tm_year = year - FIRST_YEAR;
    t->tm_mon = month;
    t->tm_mday = day;
    t->tm_isdst = -1;
    mktime(t);
}

int
main(void)
{
    int year;
    if (scanf("%d", &year) != 1 || year > MAX_YEAR || year < MIN_YEAR) {
        return 1;
    }

    struct tm t = {};
    for (int m = 0; m < MAX_MONTH; ++m) {
        int cnt_thu = 0;
        for (int d = 1; d <= MAX_DAY; d += (t.tm_wday == THU) ? WEEK : 1) {
            init_tm(&t, year, m, d);
            if (m == t.tm_mon && t.tm_wday == THU && !(++cnt_thu % MULTIPLE_WEEK) && (d % MULTIPLE_DAY)) {
                printf("%d %d\n", m + 1, d);
            }
        }
    }

    return 0;
}