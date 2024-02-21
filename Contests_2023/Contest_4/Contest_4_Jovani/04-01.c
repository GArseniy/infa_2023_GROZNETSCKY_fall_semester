#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

int
main(int argc, char *argv[]) {
    int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0777);

    for (int i = 2; i < argc; i++){
        char *p = NULL;
        errno = 0;
        long n = strtol(argv[i], &p, 0);
        if (errno || *p || p == argv[i] || (int) n != n) {
            return 1;
        }
        unsigned un = n;

        //write(fd, &un, 4);

        char *unp = ((char *) &un);
        unp += 2;
        char buf[4];

        char c = (*unp) >> 4;
        buf[0] = c;

        c = ((*unp) << 4) | ((*(--unp)) >> 4);
        buf[1] = c;

        c = (*(unp--)) & 0x0f;
        buf[2] = c;

        c = *(unp);
        buf[3] = c;

        write(fd, buf, 4);
    }
    close(fd);

    return 0;
}