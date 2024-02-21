/*
 Напишите функцию:
 ssize_t getcwd2(int fd, char *buf, size_t size);

 Параметр fd — это открытый файловый дескриптор каталога, buf — адрес начала буфера в памяти, size — размер буфера.

 Функция должна восстановить полный путь к каталогу, который открыт и связан с файловым дескриптором fd. То есть, если
 fd — корневой каталог, то полный путь к каталогу — "/". Если fd — не корневой каталог, то полный путь к этому каталогу
 начинается с "/", состоит из записей в соответствующих каталогах, являющихся каталогами, но не символическими ссылками.
 На конце полного пути "/" должен отсутствовать. Например, "/usr/local/bin" (без кавычек).
*/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ssize_t getcwd2(int fd, char *buf, size_t size) {
    DIR *start_dir = opendir(".");

    char *res = calloc(PATH_MAX + 1, sizeof(res[0]));
    fchdir(fd);

    struct stat root;
    if (lstat("/", &root) < 0) {
        fchdir(dirfd(start_dir));
        closedir(start_dir);
        return -1;
    }

    struct stat prev;
    if (lstat(".", &prev) < 0) {
        fchdir(dirfd(start_dir));
        closedir(start_dir);
        return -1;
    }

    if (prev.st_ino == root.st_ino && prev.st_dev == root.st_dev) {
        res[0] = '/';
        res[1] = '\0';
    }

    while (prev.st_ino != root.st_ino || prev.st_dev != root.st_dev) {
        chdir("..");
        DIR *cur = opendir(".");
        if (cur == NULL) {
            return -1;
        }

        struct dirent *dd;
        while ((dd = readdir(cur)) != NULL) {
            char path[PATH_MAX + 1];
            snprintf(path, PATH_MAX, "./%s", dd->d_name);
            struct stat cur_st;
            if (lstat(path, &cur_st) < 0) {
                continue;
            }

            if (cur_st.st_ino == prev.st_ino && cur_st.st_dev == prev.st_dev) {
                char tmp[PATH_MAX + 1] = {};
                snprintf(tmp, PATH_MAX, "/%s%s", dd->d_name, res);
                free(res);
                res = strdup(tmp);
                break;
            }
        }

        closedir(cur);

        if (lstat(".", &prev) < 0) {
            fchdir(dirfd(start_dir));
            closedir(start_dir);
            return -1;
        }
    }

    fchdir(dirfd(start_dir));
    closedir(start_dir);

    int len_res = strlen(res);

    if (size > 0) {
        snprintf(buf, size, "%s", res);
    }

    free(res);

    return len_res;
}

int main(int argc, char** argv) {
    DIR* d = opendir(argv[1]);
    int fd = dirfd(d);
    char buf[PATH_MAX + 1];
    printf("%ld\n", getcwd2(fd, buf, PATH_MAX));
    printf("%s\n", buf);
    closedir(d);
    return 0;
}
