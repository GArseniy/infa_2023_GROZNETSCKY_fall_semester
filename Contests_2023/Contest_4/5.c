#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int
wrap_strtol(char *str, int *x)
{
    if (!str) {
        return -1;
    }
    errno = 0;
    char *p = NULL;
    long n = strtol(str, &p, 10);
    if (errno || *p || p == str || (int) n != n) {
        errno = 0;
        return -1;
    }
    *x = n;
    return 0;
}

int
main(int argc, char **argv)
{
    if (argc != 4) {
        return 1;
    }

    int fd_out, fd_in;
    if (((fd_in = open(argv[1], O_RDONLY)) < 0) || ((fd_out = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0)) {
        return 1;
    }

    int mod;
    if (wrap_strtol(argv[3], &mod) || (mod <= 0)) {
        return 1;
    }

    long long x = 1;
    long long sum = 0;
    unsigned char byte;
    while (read(fd_in, &byte, sizeof(byte)) == sizeof(byte)) {
        for (int i = 0; i < CHAR_BIT; ++i) {
            sum += (x % mod) * (x % mod) % mod;
            int res = (sum %= mod);
            if ((byte & 1) && (write(fd_out, &res, sizeof(res)) != sizeof(res))) {
                return 1;
            }
            ++x;
            byte >>= 1;
        }
    }

    close(fd_in);
    close(fd_out);
    return 0;
}
