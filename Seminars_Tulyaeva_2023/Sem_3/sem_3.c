#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "stdio.h"

enum {
    BUF_SIZE = 1024
};


long len_file(int fd) {
    return lseek(fd, 0, 2);
}


void swap_pair_long(int fd, int off) {
    long c_start, c_end;

    lseek(fd, off * ((long) sizeof(c_start)), 0);
    read(fd, &c_start, sizeof(c_start));

    lseek(fd, (off + 1) * (-(long) sizeof(c_end)), 2);
    read(fd, &c_end, sizeof(c_end));

    lseek(fd, off * ((long) sizeof(c_start)), 0);
    write(fd, &c_end, sizeof(c_end));

    lseek(fd, (off + 1) * (-(long) sizeof(c_end)), 2);
    write(fd, &c_start, sizeof(c_start));
}


int main(int argc, char **argv) {
    /*int fd1 = open("test1.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777); // "w"
    int fd2 = creat("test2.txt", 0777); // "w"
    int fd3 = open("test3.txt", O_APPEND | O_CREAT | O_RDWR, 0777); // "a+"
    int fd4 = open("test4.txt", O_APPEND | O_EXCL | O_RDWR, 0777); // вернет отрицит число, если файл уже существует
    */

    /*if (argc < 2) {
        return 1;
    }

    int fd_out = open(argv[1], O_RDONLY, 0777);
    int fd_in = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0777);
    char buf[BUF_SIZE];
    int c;
    while ((c = read(fd_out, buf, BUF_SIZE)) > 0) {
        // write(fd_in, buf, c);
        char *p = buf;
        int n;
        while (c) {
            n = write(fd_in, p, c);
            c -= n;
            p += n;
        }
    }*/

    int fd = open(argv[1], O_RDWR, 0777);

    int n = len_file(fd) / sizeof(long);
    for (int i = 0; i < n / 2; ++i) {
        swap_pair_long(fd, i);
    }

    unsigned char m[4];
    unsigned int val = 0;
    while (read(fd, m, sizeof(m))) {
        val += m[0] << 24 | m[1] << 16 | m[2] << 8 | m[3];
    }

    return 0;
}
