#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

enum
{
    SIZE = sizeof(double)
};


int
main(int argc, char *argv[]) {
    int fd = open(argv[1], O_CREAT | O_RDWR, 0777);

    // double buf[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // write(fd, buf, SIZE * 9);
    // double buf[3];
    // read(fd, buf, 24);

    char *p = NULL;
    errno = 0;
    long n = strtol(argv[2], &p, 0);
    if (errno || *p || p == argv[2] || (int) n != n) {
        return 1;
    }

    int len = lseek(fd, 0, 2);

    if (len <= sizeof(double)) {
        return 0;
    }

    if (n * SIZE > len) {
        n = len / SIZE;
    }

    lseek(fd, 0, 0);
    double prev;
    double val;

    for (int i = 1; i < n; i++) {
        read(fd, &prev, SIZE);
        read(fd, &val, SIZE);
        lseek(fd, -SIZE, 1);
        val -= prev;

        write(fd, &val, SIZE);
        lseek(fd, -SIZE, 1);
    }

    // lseek(fd, 0, 0);
    // read(fd, buf, len);

    // for (int i = 0; i < len / SIZE; i++) {
    //     printf("%lf ", buf[i]);
    // }

    close(fd);

    return 0;
}