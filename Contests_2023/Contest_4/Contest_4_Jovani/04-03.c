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
    STRUCT_SIZE = 12,
    INT_SIZE = 4
};

void print_tree(int fd, int num) {
    int shift = num * STRUCT_SIZE;
    lseek(fd, shift, 0);

    int mas[3];
    read(fd, mas, STRUCT_SIZE);

    if (mas[1]) {
        print_tree(fd, mas[1]);
    }

    printf("%d ", mas[0]);
    // printf("%d\n", shift);

    if (mas[2]) {
        print_tree(fd, mas[2]);
    }

    return;
}

int
main(int argc, char *argv[]) {
    int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0777);


    int buf[21] = {0, 1, 2,  -6, 3, 6,  4, 5, 4,  -18, 0, 0,  25, 0, 0,  2, 0, 0,  -5, 0, 0};
    write(fd, buf, 4 * 21);

    print_tree(fd, 0);
    printf("\n");

    
    close(fd);

    return 0;
}