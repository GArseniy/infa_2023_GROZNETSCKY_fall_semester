#include <stdio.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>

enum
{
    PAGE_SIZE = 512,
    MEM_SIZE = 1 << 16,
    BASE = 16,
    MASK = 0x1ff,
    OFFSET = 9
};

int main(int argc, char **argv) {
    if (argc < 2) {
        return -1;
    }

    int mem_fd = open(argv[1], O_RDONLY);
    if (mem_fd < 0) {
        return -1;
    }
    
    errno = 0;
    char *eptr = NULL;
    int ptable_addr = (int)strtol(argv[2], &eptr, BASE);
    if (errno || *eptr || eptr == argv[2]) {
        return -1;
    }

    unsigned short *mem = mmap(NULL, MEM_SIZE, PROT_READ, MAP_SHARED, mem_fd, 0);
    if (mem == MAP_FAILED) {
        close(mem_fd);
        exit(1);
    }

    // mem + ptable_addr / 2 - адрес начала таблицы страниц
    unsigned short virt_addr;
    while (scanf("%hx", &virt_addr) == 1) {
        unsigned short off = virt_addr & MASK;
        unsigned short virt_page_num = virt_addr >> OFFSET;

        unsigned short addr = *(mem + ptable_addr / 2 + virt_page_num);
        addr |= off;

        printf("%hu\n", *(mem + addr / 2));
    }

    close(mem_fd);

    return 0;
}
