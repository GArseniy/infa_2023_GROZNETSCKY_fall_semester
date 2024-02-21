#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }

    int fd;
    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600)) < 0) {
        return 1;
    }

    unsigned x;
    while (scanf("%u", &x) == 1) {
        char bytes[4] = {};

        bytes[0] = (x >> 20) & 0x0F;
        bytes[1] = (x >> 12) & 0xFF;
        bytes[2] = (x >> 8) & 0x0F;
        bytes[3] = x & 0xFF;

        if (write(fd, bytes, sizeof(bytes)) != sizeof(bytes)) {
            return 1;
        }
    }

    close(fd);

    return 0;
}
