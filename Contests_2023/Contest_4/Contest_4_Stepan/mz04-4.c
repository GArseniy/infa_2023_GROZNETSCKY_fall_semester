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
    BYTE_SIZE = 8,
    MAX_LL = 0xFFFFFFFFFFFFFFFF
};

int
main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }

    int fd_1 = open(argv[1], O_RDWR);

    long long min;

    int read_size = read(fd_1, &min, sizeof(min));

    if (read_size == 0) {
        close(fd_1);
        return 0;
    }    

    if (read_size != sizeof(min)) {
        return 1;
    }

    int pos_of_min = 0;
    int iter = 1;
    long long a;

    while(read(fd_1, &a, sizeof(a)) == sizeof(a)) {
// LE
        printf("%lld\n", a);

        if ( a < min) {
            min = a;
            pos_of_min = iter;
        }

        iter++;
    }

    min = MAX_LL - ((unsigned long long) min) + 1;
    lseek(fd_1, pos_of_min * sizeof(min), 0);
    
    if (write(fd_1, &min, sizeof(min)) != sizeof(min)) {
        return 1;
    }

    close(fd_1);

    return 0;
}