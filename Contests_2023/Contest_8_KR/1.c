#include <stdlib.h>
#include <stdio.h>

enum
{
    SIZE_OF_MEM = 256
};

int
cmp(const void *x1, const void *x2)
{
    long long v1 = *(long long *) x1;
    long long v2 = *(long long *) x2;

    return (v1 > v2) ? 1 : ((v1 == v2) ? 0 : -1);
}

int
main(int argc, char **argv)
{
    long long *num = calloc(SIZE_OF_MEM, sizeof(*num));
    int num_size = SIZE_OF_MEM;
    int len = 0;
    while (scanf("%lld", &num[len++]) == 1) {
        if (len == num_size) {
            num = realloc(num, (num_size += SIZE_OF_MEM) * sizeof(*num));
        }
    }

    qsort(num, --len, sizeof(*num), cmp);

    long long sum = num[0];
    for (int front_i = 1, back_i = len - 1; front_i <= back_i;) {
        sum += (sum < 0) ? num[back_i--] : num[front_i++];
    }

    printf("%lld\n", sum);
    free(num);

    return 0;
}
