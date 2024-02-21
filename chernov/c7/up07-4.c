#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    BYTE_SIZE = 8
};

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDWR);
    int file_size = lseek(fd, 0, SEEK_END) * BYTE_SIZE;
    if (file_size < 0) {
        return -1;
    }

    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0 || abs(n) > file_size) {
            continue;
        }

        unsigned byte_num = (abs(n) - 1) / BYTE_SIZE;
        if (lseek(fd, byte_num, SEEK_SET) < 0) {
            return -1;
        }

        unsigned char cur;
        if (read(fd, &cur, sizeof(cur)) != sizeof(cur)) {
            return -1;
        }

        unsigned bit_set = (n > 0);
        unsigned bit_num = abs(n) - byte_num * BYTE_SIZE - 1;
        cur &= ~(unsigned char)(1u << bit_num);
        cur |= (bit_set << bit_num);

        if (lseek(fd, -(int)sizeof(cur), SEEK_CUR) < 0) {
            return -1;
        }

        if (write(fd, &cur, sizeof(cur)) != sizeof(cur)) {
            return -1;
        }
    }

    close(fd);
}
