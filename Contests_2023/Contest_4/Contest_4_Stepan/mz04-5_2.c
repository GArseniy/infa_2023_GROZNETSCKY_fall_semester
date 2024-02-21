#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <errno.h>

enum
{
    BYTE_SIZE = 8
};

int
main(int argc, char** argv)
{
    if (argc < 4) {
        return 1;
    }

    int fd_1 = open(argv[1], O_RDONLY);

    if (fd_1 < 0) {
        return 1;
    }

    int fd_2 = open(argv[2], O_TRUNC | O_WRONLY);

    if (fd_2 < 0) {
        return 1;
    }
    
    char *eptr = NULL;
    errno = 0;
    long mod = strtol(argv[3], &eptr, 10);
    if (errno || *eptr || eptr == argv[3] || (int) mod != mod) {
        return 1;
    }

    unsigned char bit_array = 0;
    long long sum = 0;
    long long n = 0;

    while(read(fd_1, &bit_array, sizeof(bit_array)) == sizeof(bit_array)) {
        for (int i = 0; i < BYTE_SIZE; i++) {

            n++;
            sum += (n * n);

            if (bit_array & 1) {
                int result = sum % mod;

                if (write(fd_2, &result, sizeof(result)) != sizeof(result)) {
                    return 1;
                }
            }

            bit_array >>= 1;
        }
    }

    if (close(fd_1) != 0) {
        return 1;
    }

    if (close(fd_2) != 0) {
        return 1;
    }

    return 0;
}