#include <stdio.h>
#include <ctype.h>

    const char BAD_DAY[] = "18446744073709551616\n";

int
main(int argc, char **argv)
{
    char c;
    char prev = ' ';
    long long triad = 0;
    int overflow = 0;
    int error = 0;

    while ((c = getchar()) != EOF) {
        if (isspace(c)) {
            if (prev != ' ' && !error) {
                if (!overflow) {
                    printf("%lld\n", triad);
                } else {
                    printf("%s", BAD_DAY);
                }
            }
            error = 0;
            prev = ' ';
            triad = 0;
            overflow = 0;

            continue;
        }

        if (c != 'a' && c != '1' && c != '0') {
            error = 1;
            continue;
        }

        prev = c;

        if (overflow) {
            continue;
        }

        overflow = __builtin_mul_overflow(triad, 3, &triad);

        if (c == 'a') {
            overflow -= __builtin_add_overflow(triad, -1, &triad);
        } else {
            overflow -= __builtin_add_overflow(triad, c - '0', &triad);
        }
    }

    if (prev != ' ' && !error) {
        if (!overflow) {
            printf("%lld\n", triad);
        } else {
            printf("%s", BAD_DAY);
        }
    }

    return 0;
}