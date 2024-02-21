/*
    Пусть дано некоторое простое число N (N > 1). Для любых двух чисел a и b (0 ≤ a, b < N) их произведение по модулю
    N c определяется как остаток от деления произведения a и b на N. Запишем это как c ≡ a * b (mod N).
    Пусть даны любые c (0 ≤ c < N) и a (0 < a < N). Тогда существует единственное b, такое что c ≡ a * b (mod N).
    Число b назовем результатом деления по модулю N числа c на число a. Запишем это как b ≡ c / a (mod N).

    На стандартный поток вывода напечатайте таблицу деления для некоторого фиксированного простого числа N.
    
    Input format
        На стандартном потоке ввода задается единственное целое простое число N (N < 2000).
    
    Output format
        На стандартный поток вывода напечатайте таблицу деления, которая состоит из N строк и N - 1 столбцов,
        где строка соответствует делимому, а столбец - делителю. Столбцов выводится N - 1, так как столбец,
        соответствующий делителю 0 пропускается.

    Пример ввода/вывода см. ./tasks/3.html
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // inverse numbers
    int* inv = calloc(n, sizeof(*inv));
    if (!inv) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        inv[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        if (inv[i] != 0) {
            continue;
        }

        for (int j = 1; j < n; j++) {
            if ((i * j) % n == 1) {
                inv[i] = j;
                inv[j] = i;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            printf("%d ", (i * inv[j]) % n);
        }

        printf("\n");
    }

    free(inv);

    return 0;
}