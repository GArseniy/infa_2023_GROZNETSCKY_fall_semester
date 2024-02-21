#include "random_source.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

const char *modulenamelin = "linear.c";

enum
{
    BASE = 10,
    MULTIPLICATOR = 1103515245,
    INCREMENT = 12345,
    MOD = 1 << 31 // 2^31
};

RandomSource *
destroylinear(RandomSource *item)
{
    free(item->ops);
    free(item);
    return NULL;
}

double
nextlinear(RandomSource *item)
{
    item->urand_or_prev = ((unsigned long long) MULTIPLICATOR * item->urand_or_prev + INCREMENT) % (unsigned) MOD;
    return (double) item->urand_or_prev / (unsigned) MOD;
};

RandomSource *
random_linear_factory(const char *params)
{
    char *endptr2 = NULL;
    unsigned int seed = strtol(params, &endptr2, BASE);
    if (errno || *endptr2 || endptr2 == params) {
        fprintf(stderr, "main: Oh no! You've entered something other than the number!\n");
        exit(1);
    }
    seed = ((seed) << 1) >> 1;
    RandomSource *ptr = calloc(1, sizeof(*ptr));
    ptr->ops = calloc(1, sizeof(*ptr->ops));
    error_report((long long) ptr->ops, modulenamelin);
    ptr->urand_or_prev = seed;
    ptr->ops->destroy = destroylinear;
    ptr->ops->next = nextlinear;
    error_report((long long) ptr, modulenamelin);
    return ptr;
};
