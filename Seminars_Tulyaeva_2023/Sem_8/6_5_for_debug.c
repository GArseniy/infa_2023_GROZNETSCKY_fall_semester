#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int
is_root(int fd)
{
    DIR *par_d;
    if (!(par_d = opendir(".."))) {
        return -1;
    }

    int par_fd = dirfd(par_d);
    struct stat cur_stat, par_stat;

    return (fstat(fd, &cur_stat) || fstat(par_fd, &par_stat) || closedir(par_d))
               ? -1
               : (cur_stat.st_dev == par_stat.st_dev && cur_stat.st_ino == par_stat.st_ino);
}

char *
get_f_name(__ino_t st_ino, __dev_t st_dev)
{
    DIR *d;
    if (!(d = opendir(".."))) {
        return NULL;
    }
    struct dirent *dd;
    struct stat buf;

    char *file_name = calloc(PATH_MAX, sizeof(*file_name));
    while ((dd = readdir(d))) {
        if (strcmp(dd->d_name, ".") != 0 && strcmp(dd->d_name, "..") != 0 &&
            (snprintf(file_name, PATH_MAX, "../%s", dd->d_name) > 0) && !lstat(file_name, &buf) &&
            buf.st_dev == st_dev && buf.st_ino == st_ino) {
            free(file_name);
            char *ret = strdup(dd->d_name);
            closedir(d);
            return ret;
        }
    }
    free(file_name);
    return NULL;
}

ssize_t
getcwd2(int fd, char *buf, size_t size)
{
    DIR *start_d = opendir(".");
    int start_fd = dirfd(start_d);
    int input_fd = fd;

    if (!start_fd || !input_fd) {
        return -1;
    }
    if (fchdir(input_fd)) {
        return -1;
    }

    char **folders = calloc(PATH_MAX, sizeof(folders[0]));
    int cnt_folders = 0;
    struct stat f_stat;
    int root_flag;
    DIR *d = NULL;

    while (!(root_flag = is_root(fd))) {
        if (fstat(fd, &f_stat)) {
            return -1;
        }
        if (!(folders[cnt_folders++] = get_f_name(f_stat.st_ino, f_stat.st_dev))) {
            return -1;
        }
        if (input_fd != fd && closedir(d)) {
            return -1;
        }
        if (!(d = opendir("..")) || !(fd = dirfd(d)) || fchdir(fd)) {
            return -1;
        }
    }
    if (root_flag == -1) {
        return -1;
    }
    if (input_fd != fd && closedir(d)) {
        return -1;
    }

    long len = 0;
    for (int i = 0; i < cnt_folders; ++i) {
        len += (long) strlen(folders[i]) + 1;
    }
    if (!size) {
        for (long i = 0; i < cnt_folders; ++i) {
            free(folders[i]);
        }
        free(folders);
        if (fchdir(start_fd) || closedir(start_d)) {
            return -1;
        }
        return len ? len : 1;
    }
    if (!len) {
        if (size == 1) {
            buf[0] = 0;
        } else {
            buf[0] = '/';
            buf[1] = 0;
        }
        for (long i = 0; i < cnt_folders; ++i) {
            free(folders[i]);
        }
        free(folders);
        if (fchdir(start_fd) || closedir(start_d)) {
            return -1;
        }
        return 1;
    }

    char *path = calloc(PATH_MAX, sizeof(*path));
    for (long i = cnt_folders - 1, cur_path_len = 0; i >= 0; --i) {
        snprintf(path + cur_path_len, PATH_MAX - cur_path_len, "/%s", folders[i]);
        cur_path_len += (long) strlen(folders[i]) + 1;
        free(folders[i]);
    }
    free(folders);

    for (int i = 0; i < size && path[i]; ++i) {
        buf[i] = path[i];
    }

    free(path);
    buf[(len >= size) ? (size - 1) : len] = 0;
    if (fchdir(start_fd) || closedir(start_d)) {
        return -1;
    }
    return len;
}

int
main(int argc, char **argv)
{
    int fd = open(".", O_RDONLY);
    size_t size = PATH_MAX;
    char buf[size];

    long long len;
    if ((len = getcwd2(fd, buf, 0)) != -1) {
        printf("%lld: \n", len);
    } else {
        printf("Хахахаххаха\n");
    }

    close(fd);
    return 0;
}