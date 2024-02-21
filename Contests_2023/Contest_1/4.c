#include "stdlib.h"

int
my_compare(const void *val1, const void *val2)
{
    int v1 = *(int *) val1;
    int v2 = *(int *) val2;
    if ((v1 & 1) != (v2 & 1)) {
        return (v1 & 1) ? 1 : -1;
    }
    if (v1 == v2) {
        return 0;
    }
    if (v1 & 1) {
        return v1 < v2 ? 1 : -1;
    }
    return v1 > v2 ? 1 : -1;
}

void
sort_even_odd(size_t count, int *data)
{
    if (data == NULL) {
        return;
    }
    qsort(data, count, sizeof(data[0]), my_compare);
}
