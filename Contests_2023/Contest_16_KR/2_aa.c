#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/file.h>
#include <stdlib.h>
#include <stdint.h>

int
parse10(const char *str, size_t *outsz, uint8_t **outb)
{
    int filed = creat("tmp123.py", 0700);

    dprintf(filed, "import os;\nimport sys;\n");
    dprintf(filed, "i=%s;\n", str);
    dprintf(filed, "sys.stdout.buffer.write(i.to_bytes(16,'big'))\nos.unlink('tmp123.py')");

    int fd[2];
    pipe(fd);

    if (!fork()) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        execlp("python3", "python3", "tmp123.py", NULL);
        _exit(1);
    }
    close(fd[1]);
    wait(NULL);

    uint8_t byte;
    int flag = 0;

    int fd1[2];
    pipe(fd1);

    size_t size = 0;
    while (read(fd[0], &byte, sizeof(byte)) > 0) {
        if (flag) {
            write(fd1[1], &byte, sizeof(byte));
            ++size;
        } else if (byte != 0) {
            flag = 1;
            write(fd1[1], &byte, sizeof(byte));
            ++size;
        }
    }
    close(fd[0]);
    close(fd1[1]);

    uint8_t *buf = calloc(size, sizeof(byte));
    for (int i = 0; i < size; ++i) {
        read(fd1[0], &byte, sizeof(byte));
        buf[size - i - 1] = byte;
    }

    close(fd1[0]);

    *outsz = size;
    *outb = buf;
    return 0;
}