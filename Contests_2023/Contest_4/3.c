#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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

    long long min;
    long index_min = 0;
    int sizeof_read = read(fd, &min, sizeof(min));
    if (sizeof_read == 0) {
        close(fd);
        return 0;
    }
    if (sizeof_read != sizeof(min)) {
        return 1;
    }

    long long cur;
    for (long i = 1; (sizeof_read = read(fd, &cur, sizeof(cur))) == sizeof(cur); ++i) {
        if (min > cur) {
            min = cur;
            index_min = i;
        }
    }

    if (sizeof_read != 0) {
        return 1;
    }

    if (min != LLONG_MIN) {
        min = -min;
    }

    if ((lseek(fd, index_min * sizeof(min), 0) != -1) && (write(fd, &min, sizeof(min)) == sizeof(min))) {
        close(fd);
        return 0;
    }

    return 1;
}
