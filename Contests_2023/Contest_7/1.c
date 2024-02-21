#include <stdio.h>
#include <ctype.h>

enum
{
    BASE = 3
};

int
main(void)
{
    char err_msg[] = "18446744073709551616\n";

    long long x = 0;
    int is_num = 0;
    int is_err = 0;

    for (int c = getchar();; c = getchar()) {
        if (isspace(c) || c == EOF) {
            if (is_num) {
                printf(is_err ? err_msg : "%lld\n", x);
            }
            if (c == EOF) {
                break;
            }
            x = is_err = is_num = 0;
            continue;
        }

        if (is_err) {
            continue;
        }

        if (c != 'a' && c != '1' && c != '0') {
            break;
        }

        is_num = 1;
        c = (c == 'a') ? -1 : c - '0';

        is_err = __builtin_mul_overflow(x, BASE, &x);
        is_err -= __builtin_add_overflow(x, c, &x);
    }

    return 0;
}