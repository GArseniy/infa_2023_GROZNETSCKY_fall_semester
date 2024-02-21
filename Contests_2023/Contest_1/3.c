#include "stdio.h"

int
fast_pow(int a, int n, int p)
{
    int result = 1;
    while (n) {
        if (n % 2) {
            result = result * a % p;
            --n;
        } else {
            a = a * a % p;
            n /= 2;
        }
    }
    return result;
}

int
is_prime(int p)
{
    if (p <= 1) {
        return 0;
    }
    for (int div = 2; div * div <= p; ++div) {
        if (!(p % div)) {
            return 0;
        }
    }
    return 1;
}

enum
{
    MIN_N = 1,
    MAX_N = 2000
};

int
main(void)
{
    int p;
    if (scanf("%d", &p) != 1) {
        return 1;
    }
    if ((p <= MIN_N) || (p >= MAX_N) || !is_prime(p)) {
        return 1;
    }
    int inverse_elems[MAX_N];
    for (int i = 1; i < p; ++i) {
        inverse_elems[i] = fast_pow(i, p - 2, p);
    }
    for (int num = 0; num < p; ++num) {
        for (int den = 1; den < p; ++den) {
            int res = num * inverse_elems[den] % p;
            printf("%d ", res);
        }
        printf("\n");
    }
    return 0;
}
