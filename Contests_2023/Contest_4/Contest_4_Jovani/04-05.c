#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

int square_sum(int n, int mod) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum = i % mod;
        sum = (sum * sum) % mod;
    }

    return sum;
}

int
main(int argc, char *argv[]) {
    int fin = open(argv[1], O_CREAT | O_RDWR, 0777);
    int fout = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0777);
    
    char *p = NULL;
    errno = 0;
    long mod = strtol(argv[3], &p, 0);
    if (errno || *p || p == argv[3] || (int) mod != mod) {
            return 1;
    }

    // char x = 0x93;
    // write(fin, &x, 1);

    int len = lseek(fin, 0, 2);
    lseek(fin, 0, 0);
    
    for (int i = 0; i < len; i++) {
        unsigned char x;
        read(fin, &x, 1);
        int shift = 1;
        while (x) {
            if (x & 1) {
                int value = square_sum(shift + 8 * i, mod);
                write(fout, &value, 4);
            }
            shift++;
            x >>= 1;
        }
    }
    
    close(fin);
    close(fout);
    return 0;
}