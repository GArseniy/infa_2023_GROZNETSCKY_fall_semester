#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    int fd1 = open(argv[1], O_RDONLY);
    long len1 = lseek(fd1, 0, 2);
    char *f1 = mmap(NULL, len1, PROT_READ, MAP_SHARED, fd1, 0);
    close(fd1);

    int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0777);
    long len2 = lseek(fd2, 0, 2);
    if (len2 < len1) {
        ftruncate(fd2, len1);
        len2 = len1;
    }

    char *f2 = mmap(NULL, len2, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
    close(fd2);

    for (int i = 0; i < len1; ++i) {
        f2[i] = f1[len1 - i - 1];
    }

    munmap(f1, len1);
    munmap(f2, len2);

    return 0;
}