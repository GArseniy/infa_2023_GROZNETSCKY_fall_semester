#include <stdio.h>

typedef short STYPE;
typedef unsigned short UTYPE;

STYPE bit_reverse(STYPE value) {
    UTYPE mask = ~(UTYPE)0;
    int cnt = 0;
    while (mask != 0) {
        cnt++;
        mask >>= 1;
    }

    cnt--;
    UTYPE res = 0;
    UTYPE u_value = (UTYPE)value;
    while (u_value != 0) {
        res |= (u_value & 1) << cnt;
        cnt--;
        u_value >>= 1;
    }

    return (STYPE)res;
}

int main(void) {
    printf("%hd\n", bit_reverse((short)-6));
}
