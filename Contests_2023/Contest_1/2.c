#include "stdio.h"

int main(void) {
    const int eng_alph_size = 26;
    const int num_size = 10;

    int mask_1 = 8;
    int mask_2 = 4;

    int shift_1 = 1;
    int shift_2 = shift_1 + num_size;
    int shift_3 = shift_2 + eng_alph_size;

    int c;
    while ((c = getchar()) >= 0) {
        if (('0' <= c) && (c <= '9')) {
            c -= '0';
            c += shift_1;
        } else if (('a' <= c) && (c <= 'z')) {
            c -= 'a';
            c += shift_2;
        } else if (('A' <= c) && (c <= 'Z')) {
            c -= 'A';
            c += shift_3;
        } else {
            continue;
        }

        c ^= mask_1;
        c &= ~mask_2;

        if (c == 0) {
            putchar('@');
            continue;
        }
        if ((shift_1 <= c) && (c < shift_1 + num_size)) {
            putchar(c - shift_1 + '0');
            continue;
        }
        if ((shift_2 <= c) && (c < shift_2 + eng_alph_size)) {
            putchar(c - shift_2 + 'a');
            continue;
        }
        if ((shift_3 <= c) && (c < shift_3 + eng_alph_size)) {
            putchar(c - shift_3+ 'A');
            continue;
        }
        if (c == 63) {
            putchar('#');
            continue;
        }
    }
}