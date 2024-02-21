#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

struct Myfile
{
    int fd;
    int size;
    char *buf;
    int pos;
    int n;
};

int
mygetc(struct Myfile *f)
{
    if (f->pos == f->n) {
        f->pos = 0;
        f->n = read(f->fd, f->buf, f->size);
        if (!f->n) {
            return EOF;
        }
    }
    return (unsigned char) f->buf[f->pos++];
}

int
main(int argc, char **argv)
{
    char str[10] = {0};
    struct Myfile f = {.size = 10, .buf = str};

    int c;
    while ((c = mygetc(&f)) != EOF) {
        printf("%c\n", c);
    }

    return 0;
}
