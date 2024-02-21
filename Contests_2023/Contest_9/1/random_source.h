#ifndef C9_01_RANDOM_SOURCE_H
#define C9_01_RANDOM_SOURCE_H

struct RandomSourceOperations;
struct RandomSource;

typedef struct RandomSource
{
    struct RandomSourceOperations *ops;
} RandomSource;

typedef struct RandomSourceOperations
{
    RandomSource *(*destroy)(RandomSource *);
    double (*next)(RandomSource *);
} RandomSourceOperations;

#endif // C9_01_RANDOM_SOURCE_H
