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
    SIZE = sizeof(long long)
};

int
main(int argc, char *argv[]) {
    int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0777);

    // long long buf[9] = {435, -27, 323, -8, 0, 18, -76, 4578, 60};
    // write(fd, buf, SIZE * 9);
    // lseek(fd, 0, 0);

    int len = lseek(fd, 0, 2) / SIZE;
    lseek(fd, 0, 0);
    if (len == 0) {
        return 0;
    }

    long long value;
    read(fd, &value, SIZE);
    long long min = value;
    int pos = 0;
    for (int i = 1; i < len; i++) {
        read(fd, &value, SIZE);
        if (value < min) {
            min = value;
            pos = i;
        }
    }

    min = -min;
    lseek(fd, pos * SIZE, 0);
    write(fd, &min, SIZE);

    // lseek(fd, 0, 0);
    // long long mas[len];
    // read(fd, mas, SIZE * len);
    // for (int i = 0; i < len; i++) {
    //     printf("%lld\n", mas[i]);
    // }

    close(fd);

    return 0;
}