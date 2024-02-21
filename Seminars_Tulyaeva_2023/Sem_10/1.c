#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
    close(fd);

    char **ptr = NULL;
    int n = (int) strtol(argv[2], ptr, 10);

    for (int i = 1; i <= n; ++i) {
        pid_t pid = fork();
        if (!pid) {
            int pfd = open(argv[1], O_RDWR);
            lseek(fd, (n - i) * sizeof(i), 0);
            write(fd, &i, sizeof(i));
            close(pfd);
            exit(0);
        }
    }

    while (wait(NULL) != -1);

    fd = open(argv[1], O_RDWR);
    for (int i = 0; i < n; ++i) {
        int x;
        read(fd, &x, sizeof(x));
        printf("%d\n", x);
    }
    close(fd);

    return 0;
}
