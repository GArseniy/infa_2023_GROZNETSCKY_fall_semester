#include "stdio.h"

int main(void) {
    double x, y;
    scanf("%lf %lf", &x, &y);

    int result = ((2 <= x) && (x <= 5) && (1 <= y) && (y <= 7) && (y >= x-2)) ? 1 : 0 ;

    printf("%d\n", result);
}
