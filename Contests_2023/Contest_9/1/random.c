#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

#include "random_source.h"

static int fd;

RandomSource *
destroy_r(RandomSource *src)
{
    close(fd);
    free(src->ops);
    free(src);
    return NULL;
}

double
next_r(RandomSource *src)
{
    unsigned long long x;
    if (read(fd, &x, sizeof(x)) != sizeof(x)) {
        exit(1);
    }
    return (double) x / (double) ULLONG_MAX;
}

RandomSource *
random_random_factory(const char *data)
{
    if ((fd = open("/dev/urandom", O_RDONLY)) < 0) {
        exit(1);
    }

    RandomSourceOperations *rr_ops = calloc(1, sizeof(*rr_ops));
    rr_ops->destroy = destroy_r;
    rr_ops->next = next_r;

    RandomSource *rr = calloc(1, sizeof(*rr));
    rr->ops = rr_ops;
    return rr;
}
