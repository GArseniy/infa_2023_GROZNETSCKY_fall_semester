#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

int
is_correct(int fd)
{
    struct stat buf;
    return !fstat(fd, &buf) && S_ISREG(buf.st_mode);
}

long
ll_sqrt(long x)
{
    long root;
    for (root = 0; root * root < x; ++root) {
    }
    return (root * root == x) ? root : -1;
}

int
main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }

    if (access(argv[1], W_OK | R_OK)) {
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd < 0 || !is_correct(fd)) {
        return 1;
    }

    long long len = lseek(fd, 0, 2) * CHAR_BIT;
    if (len < 0) {
        return 1;
    }

    long n = ll_sqrt(len);
    if (n < 0) {
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        long long shift = i * n + i;
        if (lseek(fd, shift / CHAR_BIT, 0) < 0) {
            return 1;
        }

        unsigned char byte;
        if (read(fd, &byte, sizeof(byte)) != sizeof(byte)) {
            return 1;
        }

        unsigned char mask = 1u << (CHAR_BIT - 1 - shift % CHAR_BIT);
        byte |= mask;

        if (lseek(fd, -1, 1) < 0) {
            return 1;
        }

        if (write(fd, &byte, sizeof(byte)) != sizeof(byte)) {
            return 1;
        }
    }

    return 0;
}
