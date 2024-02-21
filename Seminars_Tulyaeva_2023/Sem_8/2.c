#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDWR);
    long size = lseek(fd, 0, 2);
    char *f = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);

    int len_name = strlen(argv[2]);
    ftruncate(fd, size + len_name + 1);
    close(fd);

    memmove(f + len_name + 1, f, size);
    memmove(f, argv[1], len_name);
    f[len_name] = '\n';

    munmap(f, size);

    return 0;
}
