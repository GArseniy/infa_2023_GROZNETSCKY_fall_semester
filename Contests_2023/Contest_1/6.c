#include "stdio.h"

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);

    int stat[n];
    for (int i = 0; i < n; ++i) {
        stat[i] = 0;
    }

    int mode;
    for (int i = 0; i < m; ++i) {
        scanf("%d", &mode);

        if (mode == 1) {
            int l, r, s;
            scanf("%d %d %d", &l, &r, &s);
            for (int j = l; j < r; ++j) {
                stat[j] += s;
            }

        } else if (mode == 2) {
            int l, r;
            scanf("%d %d", &l, &r);
            int sum = 0;
            for (int j = l; j < r; ++j) {
                sum += stat[j];
            }
            printf("%d\n", sum);
        }
    }

}
