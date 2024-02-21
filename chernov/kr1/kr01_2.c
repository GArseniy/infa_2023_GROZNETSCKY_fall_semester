#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

enum
{
    BASE = 17
};

int cmp(const void *pa, const void *pb) {
    const long long *a = pa;
    const long long *b = pb;
    if (*a < *b) {
        return 1;
    }

    if (*a > *b) {
        return -1;
    }

    return 0;
}

int main(int argc, char **argv) {
    unsigned long long arr[argc - 1];

    for (int i = 1; i < argc; i++) {
        char *eptr = NULL;
        errno = 0;
        unsigned long long x = strtoll(argv[i], &eptr, BASE);
        if (errno || *eptr || eptr == argv[i] || (unsigned long long) x != x) {
            continue;
        }
        
        arr[i - 1] = x;
    }
    
    qsort(arr, argc - 1, sizeof(*arr), cmp);
    
    for (int i = 0; i < argc - 1; i++) {
        printf("%llu ", arr[i]);
    }
    printf("\n");
}
