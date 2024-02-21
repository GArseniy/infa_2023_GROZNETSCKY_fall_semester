#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    if (argc == 1) {
        return 1;
    }

    struct stat buf;
    if (lstat(argv[1], &buf) < 0) {
        return 1;
    }

    char types[] = "-dl";
    int type = 0;
    if (S_ISREG(buf.st_mode) | type++, S_ISDIR(buf.st_mode) | type++, S_ISLNK(buf.st_mode)) {
    }

    char mode[] = "rwxrwxrwx";
    mode_t m = buf.st_mode;
    for (int i = 0; i < 9; i++) {
        if (!(m & 1)) {
            mode[8 - i] = '-';
        }
        m >>= 1;
    }

    printf("%c%s", types[type], mode);

    return 0;
}
