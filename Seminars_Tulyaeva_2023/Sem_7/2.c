#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int
is_correct(char *path)
{
    struct stat buf;
    return !lstat(path, &buf) && S_ISREG(buf.st_mode);
}

int
main(int argc, char **argv)
{

    FILE *f = fopen(argv[1], "r");

    char f_name[PATH_MAX];
    char path[PATH_MAX];

    while (fgets(f_name, PATH_MAX, f)) {
        f_name[strlen(f_name) - 1] = 0;
        snprintf(path, sizeof(path), "%s/%s", argv[2], f_name);
        if (is_correct(path)) {
            continue;
        }
        puts(f_name);
        putchar('\n');
    }

    return 0;
}
