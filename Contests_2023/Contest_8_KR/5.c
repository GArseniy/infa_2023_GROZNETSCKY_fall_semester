#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int
wrap_strtoul(char *str, unsigned long *x)
{
    if (!str) {
        return 1;
    }
    char *p = NULL;
    errno = 0;
    *x = strtoul(str, &p, 10);
    return errno || *p || p == str;
}

enum
{
    SIZE_OF_MEM = 4,
    POW = 2
};

char **
create_dir_list(const char *path, unsigned long user_id, unsigned long long *size, unsigned long *cnt_dirs)
{
    if (access(path, R_OK)) {
        return NULL;
    }
    DIR *d = opendir(path);
    if (!d) {
        return NULL;
    }

    char **child_dirs = calloc(SIZE_OF_MEM, sizeof(child_dirs[0]));
    unsigned long size_of_mem = SIZE_OF_MEM;
    struct dirent *dd;
    char f_name[PATH_MAX];

    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        if (snprintf(f_name, sizeof(f_name), "%s/%s", path, dd->d_name) >= sizeof(f_name)) {
            continue;
        }
        struct stat buf;
        if (lstat(f_name, &buf)) {
            continue;
        }
        if (S_ISDIR(buf.st_mode)) {
            if (*cnt_dirs == size_of_mem) {
                child_dirs = realloc(child_dirs, (size_of_mem *= POW) * sizeof(child_dirs[0]));
            }
            child_dirs[(*cnt_dirs)++] = strdup(f_name);
        }
        if (S_ISREG(buf.st_mode) && user_id == buf.st_uid) {
            *size += buf.st_size;
        }
    }
    closedir(d);
    return realloc(child_dirs, *cnt_dirs * sizeof(child_dirs[0]));
}

unsigned long long
dir_travers(const char *path, unsigned long user_id)
{
    unsigned long long size = 0;
    unsigned long cnt_dirs = 0;
    char **child_dirs = create_dir_list(path, user_id, &size, &cnt_dirs);

    for (int i = 0; i < cnt_dirs; ++i) {
        size += dir_travers(child_dirs[i], user_id);
        free(child_dirs[i]);
    }
    free(child_dirs);

    return size;
}

int
main(int argc, char **argv)
{
    if (argc != 3) {
        return 1;
    }

    unsigned long user_id;
    if (wrap_strtoul(argv[2], &user_id)) {
        return 1;
    }

    printf("%llu\n", dir_travers(argv[1], user_id));
    return 0;
}
