/*
    В аргументах командной строки задаются 32-битные знаковые целые десятичные числа.

    На стандартный поток вывода напечатайте два числа: сначала сумму положительных аргументов командной строки,
    затем сумму отрицательных аргументов командной строки. Если чисел соответствующей категории нет, выводите 0.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv) {
    long long res1 = 0, res2 = 0;
    for (int i = 1; i < argc; i++) {
        char *eptr = NULL;
        errno = 0;
        long n = strtol(argv[i], &eptr, 10);
        if (errno || *eptr || eptr == argv[i] || (int)n != n) {
            return 1;
        }

        if (n > 0) {
            if (__builtin_add_overflow(n, res1, &res1)){
                return 1;
            }
        } else {
            if (__builtin_add_overflow(n, res2, &res2)){
                return 1;
            }
        }
    }
    
    printf("%lld\n%lld\n", res1, res2);
    
    return 0;
}