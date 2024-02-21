#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

void print_tm(struct tm time) {
    printf("year(-1900) = %d\n", time.tm_year);
    printf("mon[0:11] = %d\n", time.tm_mon);
    printf("mday[1:31] = %d\n", time.tm_mday);
    printf("hour[0:23] = %d\n", time.tm_hour);
    printf("min[0:59] = %d\n", time.tm_min);
    printf("sec[0:60] = %d\n", time.tm_sec);


    printf("yday[0:365] = %d\n", time.tm_yday);
    printf("wday[0:6] 0-sunday, 1-monday... = %d\n", time.tm_wday);
    printf("tm_isdst = %d\n", time.tm_isdst);
    printf("\n");
}


enum
{
    KNOWN_YEAR = 2021 - 1900,
    KNOWN_MON = 5 - 1,
    KNOWN_MDAY = 26,
    KNOWN_HOUR = 11,
    KNOWN_MIN = 14,
    PERIOD = ((29 * 24 + 12) * 60 + 44) * 60,
    YEAR_SHIFT = 1900,
    SHIFT_MON = 8, // 256 день в году это 12 или 13е сентрября
    SHIFT_MDAY = 13,
    SHIFT_DAY = 256
};

int main(int argc, char **argv) {
    struct tm known = {};
    known.tm_year = KNOWN_YEAR;
    known.tm_mon = KNOWN_MON;
    known.tm_mday = KNOWN_MDAY;
    known.tm_hour = KNOWN_HOUR;
    known.tm_min = KNOWN_MIN;

    time_t known_time = timegm(&known);

    int year;
    if (scanf("%d", &year) != 1) {
        return -1;
    }

    struct tm cur = {};
    cur.tm_year = year - YEAR_SHIFT;
    cur.tm_mon = SHIFT_MON;
    cur.tm_mday = SHIFT_MDAY;

    time_t cur_time = timegm(&cur);
    if (cur.tm_yday == SHIFT_DAY - 1) {
        cur.tm_mday++;
        cur_time = timegm(&cur);
    }

    long long dif = (long long)cur_time - (long long)known_time;

    long long sgn = llabs(dif) / dif;

    time_t res = cur_time + (PERIOD * (sgn == 1LL) - (dif) % PERIOD);

    gmtime_r(&res, &cur);

    int monday_cnt = 0;
    while (++cur.tm_mday) {
        timegm(&cur);

        if (cur.tm_wday == 1) {
            monday_cnt++;
            if (monday_cnt == 4) {
                break;
            }

            cur.tm_mday += 6;
        }
    }

    printf("%d-%02d-%02d\n", cur.tm_year + YEAR_SHIFT, cur.tm_mon + 1, cur.tm_mday);

    return 0;
}
