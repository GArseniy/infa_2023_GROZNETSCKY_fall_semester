#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <math.h>

enum
{
    BYTE_SIZE = 8
};

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        return -1;
    }
    
    size_t size = lseek(fd, 0, SEEK_END);
    if (size < 0) {
        return -1;    
    }

    if (size == 0) {
        return 0;
    }

    size *= BYTE_SIZE;
    size = sqrt(size);

    for (int i = 0; i < size; i++) {
        unsigned byte_num = (i * size) / BYTE_SIZE;
        if (lseek(fd, byte_num, SEEK_SET) < 0) {
            return -1;
        }

        unsigned char cur;
        if (read(fd, &cur, sizeof(cur)) != sizeof(cur)) {
            return -1;
        }

        
        unsigned bit_num = 7 - i * size + byte_num * BYTE_SIZE;
        cur |= (1u << bit_num);

        if (lseek(fd, -(int)sizeof(cur), SEEK_CUR) < 0) {
            return -1;
        }

        if (write(fd, &cur, sizeof(cur)) != sizeof(cur)) {
            return -1;
        }
    }
}
