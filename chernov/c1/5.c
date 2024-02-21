/*
    По данному числу N выведите все перестановки чисел от 1 до N в лексикографическом порядке. 

    input
        3

    output
        123
        132
        213
        231
        312
        321
*/

#include <stdio.h>
#include <stdlib.h>

void print_arr(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }

    printf("\n");
}

int permute(int* arr, int n) {
    int k = -1, l = -1;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] < arr[i + 1]) {
            k = i;
        }
    }

    if (k == -1) {
        return 0;
    }

    for (int i = k + 1; i < n; i++) {
        if (arr[i] > arr[k]) {
            l = i;
        }
    }

    int tmp = arr[k];
    arr[k] = arr[l];
    arr[l] = tmp;

    for (int i = k + 1; i <= (n + k) / 2; i++) {
        int tmp = arr[i];
        arr[i] = arr[n - i + k];
        arr[n - i + k] = tmp;
    }

    return 1;
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    int* a = calloc(n, sizeof(*a));
    if (!a) {
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        a[i - 1] = i;
    }

    print_arr(a, n);
    while (permute(a, n)) {
        print_arr(a, n);
    }

    free(a);
    return 0;
}
