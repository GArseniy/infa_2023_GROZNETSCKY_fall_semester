#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

enum
{
    START_SIZE = 4,
    BASE = 10
};

unsigned long long rec_read(const char *path, long uid) {
    if (access(path, R_OK) != 0) {
        return 0;
    }

    DIR *d = opendir(path);
    
    char **rec_dir = calloc(START_SIZE, sizeof(rec_dir[0]));
    int cur_size = 0, cur_max = START_SIZE;
    unsigned long long res = 0;
    
    struct dirent *dd;
    while ((dd = readdir(d)) != NULL) {
        char str[PATH_MAX + 1];
        snprintf(str, PATH_MAX, "%s/%s", path, dd->d_name);
        
        int len = strlen(dd->d_name);
        if ((len == 1 && dd->d_name[0] == '.') || (len == 2 && dd->d_name[0] == '.' && dd->d_name[1] == '.')) {
            continue;
        }

        struct stat buf;
        if (lstat(str, &buf) < 0) {
            continue;
        }

        if (S_ISDIR(buf.st_mode)) {
            if (cur_size < cur_max) {
                rec_dir[cur_size] = strdup(dd->d_name);
                cur_size++;
            } else {
                cur_max *= 2;
                rec_dir = realloc(rec_dir, cur_max * sizeof(rec_dir[0]));
                rec_dir[cur_size] = strdup(dd->d_name);
                cur_size++;
            }
        } else if (S_ISREG(buf.st_mode)) {
            if (access(str, R_OK) == 0 && buf.st_uid == uid) {
                res += buf.st_size;
            }
        }
    }

    closedir(d);
    for (int i = 0; i < cur_size; i++) {
        char path_tmp[PATH_MAX + 1];
        snprintf(path_tmp, PATH_MAX, "%s/%s", path, rec_dir[i]);
        free(rec_dir[i]);
        res += rec_read(path_tmp, uid);
    }
    free(rec_dir);
    
    return res;
}

int main(int argc, char **argv) {
    char *eptr = NULL;
    errno = 0;
    long uid = strtol(argv[2], &eptr, BASE);
    if (errno || *eptr || eptr == argv[2] || (int) uid != uid) {
        return -1;
    }
    
    unsigned long long res = rec_read(argv[1], uid);
    printf("%llu\n", res);
}
