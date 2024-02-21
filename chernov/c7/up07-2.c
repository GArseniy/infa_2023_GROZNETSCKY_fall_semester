/*
В аргументах командной строки задается последовательность операндов. Каждый корректный операнд представляет собой
знаковое 32-битное число, непосредственно после которого идет знак “+” или “-”, который обозначает операцию,
которую нужно выполнить. Само число может содержать суффикс ‘k’, обозначающий, что значение нужно умножить на 1000.
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    long long res = 0;
    for (int i = 1; i < argc; i++) {
        char *eptr = NULL;
        errno = 0;
        int n = (int)strtol(argv[i], &eptr, 10);
        if (errno || (*eptr != 'k' && *eptr != '+' && *eptr != '-') || (int)n != n || eptr == argv[i]) {
            continue;
        }

        if (*eptr == 'k') {
            long long new_n = n;
            if (__builtin_mul_overflow(new_n, 1000, &new_n)) {
                continue;
            }

            if (*(eptr + 1) == '+' && *(eptr + 2) == '\0') {
                res += new_n;
            } else if (*(eptr + 1) == '-' && *(eptr + 2) == '\0') {
                res -= new_n;
            }
        } else if (*eptr == '+' && *(eptr + 1) == '\0') {
            res += n;
        } else if (*eptr == '-' && *(eptr + 1) == '\0') {
            res -= n;
        }
    }

    printf("%lld\n", res);

    return 0;
}
