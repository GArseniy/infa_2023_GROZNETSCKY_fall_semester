#include <stdio.h>
#include <time.h>
#include <string.h>

enum
{
    MAX_MONTH = 11,
    MAX_DAY = 31,
    FIRST_YEAR = 1900,

    MIN_YEAR = 1902,
    MAX_YEAR = 2037,

    SAT = 6,
    SUN = 0
};

void
init_tm(struct tm *t, int year, int day)
{
    memset(t, 0, sizeof(*t));
    t->tm_year = year - FIRST_YEAR;
    t->tm_mday = day;
    t->tm_isdst = -1;
    mktime(t);
}

int
is_pow2(int x)
{
    int i;
    for (i = 1; i < x; i *= 2) {
    }
    return i == x;
}

int
main(int argc, char **argv)
{
    int year;
    if (scanf("%d", &year) != 1 || year > MAX_YEAR || year < MIN_YEAR) {
        return 1;
    }

    struct tm t = {};
    int day = 0;
    int celeb_cnt = 0;

    do {
        init_tm(&t, year, ++day);
        celeb_cnt += is_pow2(day) || t.tm_wday == SAT || t.tm_wday == SUN;
    } while (t.tm_mon != MAX_MONTH || t.tm_mday != MAX_DAY);

    printf("%d\n", celeb_cnt);

    return 0;
}
