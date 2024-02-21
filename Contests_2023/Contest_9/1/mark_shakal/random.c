#include "random_source.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

const char *modulename = "random.c";
static const long double MAX_ULLONG = ULLONG_MAX;

RandomSource *
destroyurand(RandomSource *item)
{
    close(item->urand_or_prev);
    error_report(1, modulename);
    free(item->ops);
    free(item);
    return NULL;
}

double
nexturand(RandomSource *item)
{
    unsigned long long urandinput;
    int err = read(item->urand_or_prev, &urandinput, sizeof(urandinput));
    error_report(err != -1, modulename);
    return (double) urandinput / MAX_ULLONG;
};

RandomSource *
random_random_factory(const char *params)
{
    int fd = open("/dev/urandom", O_RDONLY);
    RandomSource *ptr = calloc(1, sizeof(*ptr));
    ptr->ops = calloc(1, sizeof(*ptr->ops));
    error_report((long long) ptr->ops, modulename);
    ptr->urand_or_prev = fd;
    ptr->ops->destroy = destroyurand;
    ptr->ops->next = nexturand;
    error_report((long long) ptr, modulename);
    return ptr;
};
