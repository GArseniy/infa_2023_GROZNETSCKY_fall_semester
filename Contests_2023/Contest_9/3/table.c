#include <stdio.h>

void
calcTable()
{
    unsigned char generator = 0x1d;
    unsigned char crctable[256] = {};
    for (int div = 0; div < 256; div++) {
        unsigned char byte = (unsigned char) div;
        for (unsigned char bit = 0; bit < 8; bit++) {
            if ((byte & 0x80) != 0) {
                byte <<= 1;
                byte ^= generator;
            } else {
                byte <<= 1;
            }
        }
        crctable[div] = byte;
    }
    for (int i = 240; i < 256; i++) {
        printf("%d, ", crctable[i]);
    }
}

int
main()
{
    calcTable();
    return 0;
}