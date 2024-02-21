#include "stdio.h"

typedef int STYPE;
typedef unsigned int UTYPE;

STYPE bit_reverse(STYPE value);

int main(void) {
    STYPE a = 0;
    printf("%u", bit_reverse(a));
    return 0;
}




STYPE
bit_reverse(STYPE value)
{
    UTYPE u_value = value;
    UTYPE res = 0;
    UTYPE u = ~0;
    do {
        res <<= 1;
        res |= u_value & (UTYPE) 1;
        u_value >>= 1;
    } while (u >>= 1);
    return res;
}
