#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

enum
{
    BASE = 10
};

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, 0777);
    if (fd < 0) {
        fprintf(stderr, "Failed to open file: %s\n", argv[1]);
        return -1;
    }

    char *eptr = NULL;
    errno = 0;
    long rows = strtol(argv[2], &eptr, BASE);
    if (errno || *eptr || eptr == argv[3] || (int) rows != rows) {
        return -1;
    }

    long cols = strtol(argv[3], &eptr, BASE);
    if (errno || *eptr || eptr == argv[3] || (int) cols != cols) {
        return -1;
    }

    size_t size = rows * cols * sizeof(int);
    ftruncate(fd, size);
    int *arr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    int i = 0, j = 0, direction = 0;
    /* direction
    *  0 => right;  2 => left
    *  1 => down;   3 => up
    */

    for (int k = 1; k <= rows * cols; k++) {
        *(arr + i * cols + j) = k;
        int shifted_i = i + ((direction % 2) ? -(direction - 2) : 0);
        int shifted_j = j + (!(direction % 2) ? -(direction - 1) : 0);
        
        if (shifted_i == rows || shifted_i == -1 || shifted_j == cols || \
            shifted_j == -1 || *(arr + shifted_i * cols + shifted_j) != 0) {
            
            direction = (direction + 1) % 4;

            shifted_i = i + ((direction % 2) ? -(direction - 2) : 0);
            shifted_j = j + (!(direction % 2) ? -(direction - 1) : 0);
        }

        i = shifted_i;
        j = shifted_j;
    }
}
