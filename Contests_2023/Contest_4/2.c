#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
wrap_strtol(char *str, long *x)
{
    if (!str) {
        return 1;
    }
    char *p = NULL;
    errno = 0;
    *x = strtol(str, &p, 10);
    return errno || *p || p == str;
}

int
main(int argc, char **argv)
{
    if (argc != 3) {
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        return 1;
    }

    long n;
    if (wrap_strtol(argv[2], &n)) {
        return 1;
    }

    double prev = 0;
    double cur = 0;

    long len = lseek(fd, 0, 2) / sizeof(cur);
    long stop = len > n ? n : len;

    for (long i = 0; i < stop; ++i) {
        if ((lseek(fd, i * sizeof(cur), 0) == -1) || (read(fd, &cur, sizeof(cur)) != sizeof(cur))) {
            return 1;
        }
        cur -= prev;
        prev = cur;
        if ((lseek(fd, i * sizeof(cur), 0) == -1) || (write(fd, &cur, sizeof(cur)) != sizeof(cur))) {
            return 1;
        }
    }

    close(fd);
    return 0;
}
