#include <stdio.h>
#include <stdlib.h>

enum
{
    SIZE_START = 4
};

int cmp(const void *pa, const void *pb) {
    const long long *a = pa;
    const long long *b = pb;
    if (*a > *b) {
        return 1;
    }

    if (*a < *b) {
        return -1;
    }

    return 0;
}

int main(int argc, char **argv) {
    long long *arr = calloc(SIZE_START, sizeof(*arr));
    int i = 0, cur_size = SIZE_START;
    while (scanf("%lld", &arr[i++]) == 1) {
        if (i == cur_size) {
            cur_size *= 2;
            arr = realloc(arr, cur_size * sizeof(*arr));
        }
    }
    
    i--;
    qsort(arr, i, sizeof(*arr), cmp);
    
    long long res = 0;
    for (int j = 0; j < (i + 1) / 2; j++) {
        if (j == i - j - 1) {
            res += arr[j];
            continue;
        }

        res += arr[j];
        res += arr[i - j - 1];
    }

    printf("%lld\n", res);
    
    free(arr);
}
