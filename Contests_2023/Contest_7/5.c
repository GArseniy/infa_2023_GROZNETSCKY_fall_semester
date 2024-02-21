#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

enum
{
    FIRST_YEAR = 1900,
    MIN_YEAR = 1902,
    MAX_YEAR = 2037,

    MONDAY = 1,
    CNT_MONDAY = 4,
    SHIFT = 256,
    PERIOD = ((29 * 24 + 12) * 60 + 44) * 60,

    MOON_YEAR = 2021,
    MOON_MONTH = 5,
    MOON_DAY = 26,
    MOON_HOUR = 11,
    MOON_MIN = 14,
    MOON_SEC = 0
};

int
main(int argc, char **argv)
{
    struct tm moon;
    memset(&moon, 0, sizeof(moon));
    moon.tm_year = MOON_YEAR - FIRST_YEAR;
    moon.tm_mon = MOON_MONTH - 1;
    moon.tm_mday = MOON_DAY;
    moon.tm_hour = MOON_HOUR;
    moon.tm_min = MOON_MIN;
    moon.tm_sec = MOON_SEC;
    moon.tm_isdst = -1;

    time_t moon_utc;
    if ((errno = 0, (moon_utc = mktime(&moon)) == -1) && errno) {
        return 1;
    }

    int year;
    if (scanf("%d", &year) != 1 || year > MAX_YEAR || year < MIN_YEAR) {
        return 1;
    }

    struct tm celeb;
    memset(&celeb, 0, sizeof(celeb));
    celeb.tm_year = year - FIRST_YEAR;
    celeb.tm_mday = SHIFT;
    celeb.tm_isdst = -1;

    time_t celeb_utc;
    if ((errno = 0, (celeb_utc = mktime(&celeb)) == -1) && errno) {
        return 1;
    }

    time_t diff = celeb_utc - moon_utc;
    diff %= PERIOD;
    diff -= PERIOD * (diff >= 0);
    celeb_utc -= diff;
    gmtime_r(&celeb_utc, &celeb);

    ++celeb.tm_mday;
    mktime(&celeb);

    for (int i = 0; i < CNT_MONDAY; i += (celeb.tm_wday == MONDAY)) {
        ++celeb.tm_mday;
        mktime(&celeb);
    }

    printf("%d-%02d-%02d\n", celeb.tm_year + FIRST_YEAR, celeb.tm_mon + 1, celeb.tm_mday);
    return 0;
}
