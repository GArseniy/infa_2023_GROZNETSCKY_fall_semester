#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

enum
{
    SIZE = 4
};

int
main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }

    int fd_1;
    
    fd_1 = creat(argv[1], 0600);
    
    if (fd_1 < 0) {
        return 1;
    }

    unsigned int a;
    while(scanf("%u", &a) == 1) {
        char blocks[4] = {};

        blocks[0] =( a & (0x0F << 20) )>> 20;
        blocks[1] =( a & (0xFF << 12) )>> 12;
        blocks[2] =( a & (0x0F << 8) )>> 8;
        blocks[3] = a & 0xFF;

        if (write(fd_1, blocks, SIZE) != SIZE) {
            return 1;
        }
    }

    close(fd_1);

    return 0;
}