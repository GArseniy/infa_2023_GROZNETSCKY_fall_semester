#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int
main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        return 1;
    }

    long long file_size = lseek(fd, 0, 2) * CHAR_BIT;
    if (file_size < 0) {
        return 1;
    }

    int x;
    while (scanf("%d", &x) == 1) {
        unsigned int abs_x = abs(x);
        if (!abs_x || abs_x > file_size) {
            continue;
        }

        if (lseek(fd, (abs_x - 1) / CHAR_BIT, 0) < 0) {
            return 1;
        }

        unsigned char x_byte;
        if (read(fd, &x_byte, sizeof(x_byte)) != sizeof(x_byte)) {
            return 1;
        }

        unsigned char mask = 1u << (abs_x - 1) % CHAR_BIT;
        x_byte = (x_byte & ~mask) ^ mask * (x > 0);

        if (lseek(fd, -1, 1) < 0) {
            return 1;
        }

        if (write(fd, &x_byte, sizeof(x_byte)) != sizeof(x_byte)) {
            return 1;
        }
    }

    close(fd);
    return 0;
}
