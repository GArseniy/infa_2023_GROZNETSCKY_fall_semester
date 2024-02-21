#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

int
main(int argc, char **argv)
{
    if (argc != 3) {
        return 1;
    }

    DIR *dir1, *dir2;
    if ((dir1 = opendir(argv[1])) < 0 || (dir2 = opendir(argv[2])) < 0) {
        return 1;
    }

    unsigned long long size = 0;
    struct dirent *dd;
    struct stat buf;
    char file_name[PATH_MAX];

    while ((dd = readdir(dir1))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..") ||
            snprintf(file_name, sizeof(file_name), "%s/%s", argv[1], dd->d_name) >= sizeof(file_name) ||
            lstat(file_name, &buf) || !S_ISREG(buf.st_mode) || access(file_name, W_OK)) {
            continue;
        }
        __ino_t st_ino = buf.st_ino;
        __dev_t st_dev = buf.st_dev;
        seekdir(dir2, 0);
        while ((dd = readdir(dir2))) {
            if (strcmp(dd->d_name, ".") != 0 && strcmp(dd->d_name, "..") != 0 &&
                snprintf(file_name, sizeof(file_name), "%s/%s", argv[2], dd->d_name) < sizeof(file_name) &&
                !stat(file_name, &buf) && buf.st_ino == st_ino && buf.st_dev == st_dev) {
                size += buf.st_size;
                break;
            }
        }
    }

    closedir(dir1);
    closedir(dir2);

    printf("%lld\n", size);

    return 0;
}
