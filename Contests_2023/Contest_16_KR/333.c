#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int
main(int argc, char const *argv[])
{
    int base, s, i;
    scanf("%d%d%d", &base, &s, &i);

    long long cnt = base / s;

    long long x;
    int n;

    while (scanf("%lld", &x) > 0) {
        if (x % base) {
            x = (x / base) + 1;
        } else {
            x /= base;
        }
        if (x <= i) {
            printf("0\n");
            continue;
        }
        x -= i;
        if (x <= cnt) {
            printf("1\n");
            continue;
        }

        x -= cnt;
        n = 2;
        if (x <= cnt * cnt) {
            n += x / cnt;
            if (x % cnt) {
                n++;
            }
            printf("%d\n", n);
            continue;
        }

        x -= cnt * cnt;
        n += cnt + 1;

        if (x > cnt * cnt * cnt) {
            printf("-1\n");
            continue;
        }
        n += (x / (cnt * cnt)) * (cnt + 1);
        if (x % (cnt * cnt)) {
            n += x / cnt;
            if (x % cnt) {
                n++;
            }
        }

        printf("%d\n", n);
    }

    return 0;
}
