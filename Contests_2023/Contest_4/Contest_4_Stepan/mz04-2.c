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
    BYTE_SIZE = 8
};

int
main(int argc, char** argv)
{
    if (argc < 3) {
        return 1;
    }

    int fd_1 = open(argv[1], O_RDWR);

    char *eptr = NULL;
    errno = 0;
    
    long n = strtol(argv[2], &eptr, 10);
    
    if (errno || *eptr || eptr == argv[2] || (int) n != n) {
        // printf("strtol problem\n");
        return 1;
    }

    if (n < 2) {
        close(fd_1);
        return 0;
    }

    double need_to_change_num = 0;
    double changing_param = 0;
    int size = sizeof(need_to_change_num);

    int reading_bytes = read(fd_1, &changing_param, size);

    if (reading_bytes == 0) {
        close(fd_1);
        return 0;   //empty file
    }

    if (reading_bytes != size) {
        // printf("changing_param is not read\n");
        return 1;
    }

    for (int i = 1; i < n; i++) {

        reading_bytes = read(fd_1, &need_to_change_num, size);

        if (reading_bytes == 0) {
            close(fd_1);
            return 0; // end of file, n > count_of_numbers
        }

        if (reading_bytes != size) {
            // printf("need_to_change_num is not read\n");
            return 1;
        }

        need_to_change_num -= changing_param;

        lseek(fd_1, -size, 1);
        if (write(fd_1, &need_to_change_num, size) != size) {
            return 1;
        }

        changing_param = need_to_change_num;
        need_to_change_num = 0.0;
    }

    close(fd_1);

    return 0;
}