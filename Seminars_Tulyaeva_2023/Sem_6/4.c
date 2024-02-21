#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

enum
{
    MAX_MONTH = 12,
    FIRST_YEAR = 1900,
};

int
main(int argc, char **argv)
{
    char **ptr;
    int year = strtol(argv[1], ptr, 0);
    int day = strtol(argv[2], ptr, 0);
    int week_day = strtol(argv[3], ptr, 0);

    struct tm t = {};
    int cnt = 0;
    for (int m = 0; m < MAX_MONTH; ++m) {
        memset(&t, 0, sizeof(t));
        t.tm_year = year - FIRST_YEAR;
        t.tm_mon = m;
        t.tm_mday = day;
        t.tm_isdst = -1;

        mktime(&t);

        if (t.tm_mday == day && t.tm_wday == week_day) {
            cnt++;
        }
    }

    printf("%d\n", cnt);
    return 0;
}
