#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int
wrap_strtol(char *str, long *x)
{
    if (!str) {
        return 1;
    }
    char *p = NULL;
    errno = 0;
    *x = strtol(str, &p, 10);
    return errno || *p || p == str;
}

enum
{
    SIZE_OF_MEM = 64,
    MAX_REC_DEPTH = 4
};

void
dir_travers(const char *path, long max_size, int rec_depth)
{
    static unsigned long len_of_first_dir = 0;
    static int is_first_dir = 1;
    if (is_first_dir) {
        is_first_dir = 0;
        len_of_first_dir = strlen(path);
    }

    if (access(path, R_OK)) {
        return;
    }

    DIR *d = opendir(path);
    if (!d) {
        return;
    }

    char **child_dirs = calloc(SIZE_OF_MEM, sizeof(child_dirs[0]));
    unsigned long cnt_dirs = 0;
    unsigned long size_of_mem = SIZE_OF_MEM;
    struct dirent *dd;
    char f_name[PATH_MAX + 1];

    while ((dd = readdir(d))) {
        snprintf(f_name, PATH_MAX + 1, "%s/%s", path, dd->d_name);

        if ((dd->d_name[0] == '.' && dd->d_name[1] == 0) ||
            (dd->d_name[0] == '.' && dd->d_name[1] == '.' && dd->d_name[2] == 0)) {
            continue;
        }

        struct stat buf;
        if (lstat(f_name, &buf)) {
            continue;
        }

        if (S_ISDIR(buf.st_mode) && rec_depth < MAX_REC_DEPTH) {
            if (cnt_dirs >= size_of_mem) {
                child_dirs = realloc(child_dirs, (size_of_mem += SIZE_OF_MEM) * sizeof(child_dirs[0]));
            }
            child_dirs[cnt_dirs++] = strdup(f_name);
        }

        if (S_ISREG(buf.st_mode) && !access(f_name, R_OK) && buf.st_size <= max_size) {
            printf("%s\n", f_name + len_of_first_dir + 1);
        }
    }
    closedir(d);

    for (int i = 0; i < cnt_dirs; ++i) {
        dir_travers(child_dirs[i], max_size, rec_depth + 1);
        free(child_dirs[i]);
    }
    free(child_dirs);
}

int
main(int argc, char **argv)
{
    if (argc != 3) {
        return 1;
    }

    long max_size;
    if (wrap_strtol(argv[2], &max_size)) {
        return 1;
    }

    dir_travers(argv[1], max_size, 1);
    return 0;
}
