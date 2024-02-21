#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"

int
my_atod(char *str, double *x)
{
    char *p = NULL;
    *x = strtod(str, &p);
    return (errno || *p || p == str);
}

enum
{
    MAX_COURSE = 10000,
    MIN_COURSE = 0
};

enum
{
    MAX_PERCENT = 100,
    MIN_PERCENT = -100
};

enum
{
    PRECISION = 10000
};

int
main(int argc, char *argv[])
{
    double course;
    if (argc == 1 || my_atod(argv[1], &course) || course > MAX_COURSE || course <= MIN_COURSE) {
        return 1;
    }
    course *= PRECISION;
    for (int i = 2; i < argc; ++i) {
        double percent;
        if (my_atod(argv[i], &percent) || percent > MAX_PERCENT || percent < MIN_PERCENT) {
            errno = 0;
            continue;
        }
        course += percent * course / 100;
        course = round(course);
    }
    course /= PRECISION;
    printf("%.4f\n", course);
    return 0;
}
