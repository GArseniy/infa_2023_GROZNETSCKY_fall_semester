#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define format_s " %d/%d/%d %d:%d:%d "

enum
{
    FIRST_YEAR = 1900
};

int
main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    FILE *stream = fdopen(fd, "r");

    int year, mon, day, hour, min, sec;
    if (fscanf(stream, format_s, &year, &mon, &day, &hour, &min, &sec) != 6) {
        return 1;
    }

    struct tm t_prev;
    memset(&t_prev, 0, sizeof(t_prev));
    t_prev.tm_year = year - FIRST_YEAR;
    t_prev.tm_mon = mon - 1;
    t_prev.tm_mday = day;
    t_prev.tm_hour = hour;
    t_prev.tm_min = min;
    t_prev.tm_sec = sec;
    time_t prev_utc = timegm(&t_prev);

    while (fscanf(stream, format_s, &year, &mon, &day, &hour, &min, &sec) == 6) {
        struct tm t_cur;
        memset(&t_cur, 0, sizeof(t_cur));
        t_cur.tm_year = year - FIRST_YEAR;
        t_cur.tm_mon = mon - 1;
        t_cur.tm_mday = day;
        t_cur.tm_hour = hour;
        t_cur.tm_min = min;
        t_cur.tm_sec = sec;
        time_t cur_utc = timegm(&t_cur);

        printf("%ld\n", cur_utc - prev_utc);
        prev_utc = cur_utc;
    }

    return 0;
}
