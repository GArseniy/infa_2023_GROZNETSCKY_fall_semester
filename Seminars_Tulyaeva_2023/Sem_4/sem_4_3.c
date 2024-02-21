#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "stdio.h"
#include <string.h>

int
main(int argc, char **argv)
{
    if (argc == 1) {
        return 1;
    }

    struct stat buf;

    if (lstat(argv[1], &buf)) {
        return 1;
    }

    if (S_ISDIR(buf.st_mode)) {
        int sizeof_s = len(argv[1]) + 4;
        char f_name[sizeof_s + 1];
        snprintf(f_name, sizeof_s, "%s.uid", argv[0]);
        int fd;
        if (fd = open(f_name, O_CREAT | O_TRUNC | O_WRONLY, 0777) < 0) {
            return 1;
        }
        write(fd, );
    }
    if (S_ISREG(buf.st_mode)) {
    }

    return 0;
}
