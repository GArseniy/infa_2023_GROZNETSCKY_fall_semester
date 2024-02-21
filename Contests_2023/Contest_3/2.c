#include <stdlib.h>
#include "stdio.h"
#include "errno.h"

int
main(int argc, char *argv[])
{
    long long int pos_sum = 0, neg_sum = 0;
    while (--argc) {
        char *p = NULL;
        long n = strtol(argv[argc], &p, 10);
        if (errno || *p || p == argv[argc] || (int) n != n) {
            errno = 0;
            continue;
        }
        if (n > 0) {
            pos_sum += n;
        } else {
            neg_sum += n;
        }
    }
    printf("%lld\n%lld\n", pos_sum, neg_sum);
    return 0;
}
