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

void print_arr(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
}

int main(void) {
	int n = 10;
	int a[10] = {1, -20, 120, 3, 4, -123, 2000000000, -2000000000, 2000000001};
	// int* a = calloc(n, sizeof(int));
	// for (int i = 0; i < n; i++) {
	// 	a[i] = i;
	// }

	sort_even_odd(n, a);
	print_arr(a, n);

	// free(a);
}
