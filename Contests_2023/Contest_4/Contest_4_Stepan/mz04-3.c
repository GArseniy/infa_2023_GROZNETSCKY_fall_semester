#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <errno.h>

enum
{
    SIZEOF_STRUCT_NODE = 3*sizeof(int),
    SHIFT = sizeof(int)
};

void
print_desc(int fd, int pos)
{
    // print_desc(right)
    lseek(fd, pos*SIZEOF_STRUCT_NODE + 2*SHIFT, 0);
    int right_idx;

    if (read(fd, &right_idx, sizeof(right_idx)) < 0) {
        return;
    }

    if (right_idx != 0) {
        print_desc(fd, right_idx);
    }

    // print
    lseek(fd, pos*SIZEOF_STRUCT_NODE, 0);
    int key = 0;
    
    if (read(fd, &key, sizeof(key)) < 0) {
        return;
    }

    printf("%d ", key);
    
    // print_desc(left)
    lseek(fd, pos*SIZEOF_STRUCT_NODE + SHIFT, 0);
    int left_idx;
    
    if (read(fd, &left_idx, sizeof(left_idx)) < 0) {
        return;
    }

    if (left_idx != 0) {
        print_desc(fd, left_idx);
    }

}

int
main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }

    int fd_1 = open(argv[1], O_RDWR);

    print_desc(fd_1, 0);
    printf("\n");

    close(fd_1);

    return 0;
}