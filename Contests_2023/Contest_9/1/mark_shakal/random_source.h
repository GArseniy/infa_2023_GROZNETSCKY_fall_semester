#ifndef HEADER
#define HEADER
typedef struct RandomSource RandomSource;
typedef struct RandomSourceOperations RandomSourceOperations;
typedef RandomSource *(*cast_random_factory)(const char *);
struct RandomSourceOperations
{
    double (*next)(RandomSource *item);
    RandomSource *(*destroy)(RandomSource *item);
};

struct RandomSource
{
    RandomSourceOperations *ops;
    unsigned long long urand_or_prev;
};

void error_report(long long error, const char *modulename);
RandomSource *random_linear_factory(const char *params);
RandomSource *random_random_factory(const char *params);
#endif
