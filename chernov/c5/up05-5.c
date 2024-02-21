/*
 Напишите функцию:
 int copy_file(const char *srcpath, const char *dstpath);

 srcpath должен быть путем к существующему файлу, доступному на чтение. srcpath не должен быть каталогом.

 Если dstpath существует и является каталогом, то файл srcpath должен быть скопирован в каталог dstpath, при этом имя файла
 в каталоге dstpath должно совпадать с последней компонентой пути srcpath.

 Если dstpath не существует или не является каталогом, файл dstpath перезаписывается.

 Должна быть предусмотрена защита в случае, когда входной файл совпадает с выходным файлом.
 В этом случае должно возвращаться 0 и не выполняться никаких действий.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

enum
{
    BUF_SIZE = 4096,
    MODE_MASK = 0x1ff
};

int copy_file(const char *srcpath, const char *dstpath) {
    struct stat src, dst;
    if (stat(srcpath, &src) < 0) {
        return -1;
    }

    if (access(srcpath, R_OK) != 0) {
        return -1;
    }

    int dst_fd = -1;

    if (stat(dstpath, &dst) < 0) {
        dst_fd = open(dstpath, O_TRUNC | O_CREAT | O_WRONLY, src.st_mode & MODE_MASK);
        if (dst_fd < 0) {
            return -1;
        }
    } else if (!S_ISDIR(dst.st_mode)) {
        if (src.st_ino == dst.st_ino && src.st_dev == dst.st_dev) {
            return 0;
        }

        dst_fd = open(dstpath, O_TRUNC | O_CREAT | O_WRONLY, src.st_mode & MODE_MASK);
        if (dst_fd < 0) {
            return -1;
        }
    }

    int src_fd = open(srcpath, O_RDONLY);
    if (src_fd < 0) {
        return -1;
    }

    if (dst_fd < 0) {
        char *p = (char *)srcpath;
        int len = strlen(srcpath) - 1;
        p += len;
        while (len-- > 0 && *p != '/') {
            p--;
        }

        char dest[PATH_MAX + 1];
        sprintf(dest, "%s/%s", dstpath, p);

        struct stat tmp_stat;
        if (stat(dest, &tmp_stat) == 0) {
            if (tmp_stat.st_ino == src.st_ino && tmp_stat.st_dev == src.st_dev) {
                return 0;
            }
        }

        dst_fd = open(dest, O_TRUNC | O_CREAT | O_WRONLY, src.st_mode & MODE_MASK);
        if (dst_fd < 0) {
            return -1;
        }
    }

    char buf[BUF_SIZE];
    int c;
    while ((c = read(src_fd, buf, BUF_SIZE)) > 0) {
        int shift = 0;
        while (c > 0) {
            int written = write(dst_fd, buf + shift, c);
            if (written < 0) {
                return -1;
            }

            shift += written;
            c -= written;
        }
    }

    return 0;
}
