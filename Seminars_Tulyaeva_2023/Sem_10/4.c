#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
int
main(int argc, char **argv)
{
    char c = 'a';
    int fd;
    fd = open("test.txt", O_RDONLY);
    if (fork()) {
        int fd2 = open("test.txt", O_RDONLY);
        int fd3 = dup(fd);
        lseek(fd, 2, 1);
        wait(NULL);
        read(fd2, &c, 1);
        write(1, &c, 1);
        read(fd3, &c, 1);
        write(1, &c, 1);
    } else {
        read(fd, &c, 1);
        write(1, &c, 1);
    }
    return 0;
}
// aad
// cad