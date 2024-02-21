#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

enum
{
    SHIFT = 9,
    MASK = 0x007F
};

int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDWR);
    long size = lseek(fd, 0, 2);
    unsigned char *f = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    char *p = NULL;
    long vtb = strtol(argv[2], &p, 10);

    unsigned short virt_addr;
    while (scanf("%hd", &virt_addr) == 1) {
        unsigned short offset = virt_addr >> SHIFT;
        unsigned short fact_addr = f[vtb + offset] | virt_addr & MASK;
        printf("%d\n", f[fact_addr]);
    }

    return 0;
}