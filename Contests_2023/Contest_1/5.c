#include "stdio.h"

void
print_perms(int n, int len, int *used, int *perm)
{
    if (len == 0) {
        for (int i = 0; i < n; ++i) {
            printf("%d", perm[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            perm[n - len] = i + 1;
            used[i] = 1;
            print_perms(n, len - 1, used, perm);
            used[i] = 0;
        }
    }
}

enum
{
    MIN_N = 0,
    MAX_N = 10
};

int
main(void)
{
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if ((n <= MIN_N) || (n >= MAX_N)) {
        return 1;
    }
    int used[MAX_N] = {0};
    int perm[MAX_N];
    print_perms(n, n, used, perm);
    return 0;
}
