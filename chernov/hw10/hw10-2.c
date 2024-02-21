#include <stdio.h>
#include <stdlib.h>

enum
{
    M = 1103515245,
    C = 12345,
    MOD = 1 << 31
};

double pow(double x, double y);

struct RandomGenerator;
int next(struct RandomGenerator *rr);
void destroy(struct RandomGenerator *rr);

struct operations {
    int (*next) (struct RandomGenerator *);
    void (*destroy) (struct RandomGenerator *);
};

struct operations OPS = {&next, &destroy};

typedef struct RandomGenerator {
    struct operations *ops;
    unsigned int cur_x;
} RandomGenerator;

RandomGenerator *random_create(int seed) {
    RandomGenerator *rr = calloc(1, sizeof(*rr));
    rr->ops = &OPS;
    rr->cur_x = seed;

    return rr;
}

int next(RandomGenerator *rr) {
    rr->cur_x = (M * rr->cur_x + C) % MOD;
    return rr->cur_x;
}

void destroy(RandomGenerator *rr) {
    free(rr);
}
