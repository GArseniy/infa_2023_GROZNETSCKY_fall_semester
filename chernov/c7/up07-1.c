/*
 Рассмотрим троичную симметричную систему счисления. В троичной симметричной системе счисления
 используются три цифры '0', '1', 'a'. Цифра 'a' имеет значение -1, веса позиций являются степенью числа 3,
 как обычно. Число 'a1' равно -1 * 3 + 1 = -2 в десятичной системе счисления.

 На стандартном потоке ввода задается последовательность чисел, записанных в троичной симметричной системе счисления.
 Числа разделяются произвольным количеством пробельных символов. Перед первым числом и после последнего числа может следовать
 произвольное количество пробельных символов.

 Если очередное число представимо 64-битным знаковым двоичным числом, на стандартный вывод напечатайте его в десятичном виде.
 Если очередное число непредставимо 64-битным знаковым двоичным числом, на стандартный вывод напечатайте '18446744073709551616'.
 Каждое число выводите на отдельной строке.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ERR_PRINT "18446744073709551616\n"

enum
{
    BASE = 3
};

int main(int argc, char **argv) {
    int c;
    long long res = 0;
    int waits_for_print = 0, skip_flag = 0;
    while ((c = getc(stdin)) != EOF) {
        if (c == ' ' || c == '\n') {
            if (waits_for_print) {
                printf("%lld\n", res);
            }

            waits_for_print = 0;
            skip_flag = 0;
            res = 0;
            continue;
        }

        if (skip_flag) {
            continue;
        }

        switch (c) {
            case '1':
                c = 1;
                break;
            case 'a':
                c = -1;
                break;
            case '0':
                c = 0;
        }

        if (__builtin_mul_overflow(res, BASE, &res)) {
            if (__builtin_add_overflow(res, 1, &res)) {
                c -= 1;
            } else {
                printf(ERR_PRINT);
                waits_for_print = 0;
                skip_flag = 1;
                continue;
            }
        }

        if (__builtin_add_overflow(res, c, &res)) {
            printf(ERR_PRINT);
            waits_for_print = 0;
            skip_flag = 1;
            continue;
        }

        waits_for_print = 1;
    }

    return 0;
}
