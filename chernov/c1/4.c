/*
    Напишите функцию sort_even_odd с прототипом.
    void sort_even_odd(size_t count, int *data)

    функция должна отсортировать массив так, чтобы сначала в нем шли четные числа по неубыванию,
    потом нечетные числа по невозрастанию.
*/

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *x, const void *y) {
    const int *a1 = (const int*) x;
    const int *a2 = (const int*) y;

    if (!(*a2 & 1) && *a1 & 1) {
        return 1;
    } else if (*a1 & 1 && *a2 & 1) {
        return *a2 > *a1 ? 1 : (*a2 < *a1 ? -1 : 0);
    } else if (!(*a1 & 1) && !(*a2 & 1)) {
        return *a1 > *a2 ? 1 : (*a1 < *a2 ? -1 : 0);
    }

    return 0;
}

void sort_even_odd(size_t count, int *data) {
    if (data == NULL) {
        return;
    }

    qsort(data, count, sizeof(data[0]), cmp);
}
