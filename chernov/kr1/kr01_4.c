#include <time.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    YEAR_SHIFT = 1900
};

int main(int argc, char **argv) {
    int year;
    if (scanf("%d", &year) != 1) {
        return -1;
    }
    
    struct tm tm = {};
    tm.tm_year = year - YEAR_SHIFT;
    tm.tm_mday = 1;
    tm.tm_isdst = -1;
    
    mktime(&tm);
    
    int cur_holiday = 1, answ = 0;
    while (tm.tm_year == year - YEAR_SHIFT) {
        if (tm.tm_yday + 1 == cur_holiday) {
            cur_holiday *= 2;
            answ++;
        } else if (tm.tm_wday == 0 || tm.tm_wday == 6) {
            answ++;
        }

        tm.tm_mday++;
        tm.tm_isdst = -1;
        mktime(&tm);
    }
    
    printf("%d\n", answ);
}
