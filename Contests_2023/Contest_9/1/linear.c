#include <errno.h>
#include <stdlib.h>

#include "random_source.h"

int
wrap_strtoll(const char *str, int *x)
{
    if (!str) {
        return -1;
    }
    errno = 0;
    char *p = NULL;
    long long n = strtoll(str, &p, 10);
    if (errno || *p || p == str || (int) n != n) {
        errno = 0;
        return -1;
    }
    *x = (int) n;
    return 0;
}

static unsigned long int next_num;

enum
{
    A = 1103515245,
    C = 12345,
    MOD = 0x80000000,
    SEED_MASK = 0x7FFFFFFF
};

RandomSource *
destroy_l(RandomSource *src)
{
    free(src->ops);
    free(src);
    return NULL;
}

double
next_l(RandomSource *src)
{
    next_num = (next_num * A + C) % MOD;
    return (double) next_num / MOD;
}

RandomSource *
random_linear_factory(const char *str_seed)
{
    int seed;
    if (wrap_strtoll(str_seed, &seed)) {
        exit(1);
    }
    seed &= SEED_MASK;
    next_num = seed;

    RandomSourceOperations *rr_ops = calloc(1, sizeof(*rr_ops));
    rr_ops->destroy = destroy_l;
    rr_ops->next = next_l;

    RandomSource *rr = calloc(1, sizeof(*rr));
    rr->ops = rr_ops;
    return rr;
}
