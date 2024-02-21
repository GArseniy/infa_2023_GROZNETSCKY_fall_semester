/*
 В аргументе командной строки передается путь к каталогу D и максимальный размер Z.

 На стандартный поток вывода напечатайте относительные пути к регулярным файлам, которые доступны на чтение текущему
 пользователю и имеют размер не больше Z. Подкаталоги обрабатывайте рекурсивно на глубину не более 4. Каждый путь выводите на
 отдельной строке. Относительные пути не должны содержать каталогов . и ..
*/

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
    MAX = 4
};

void rec_read(const char *path, int max_size, int deep, int print_shift) {
    if (access(path, R_OK) != 0) {
        return;
    }

    DIR *d = opendir(path);
    
    char **rec_dir = calloc(MAX, sizeof(rec_dir[0]));
    int cur_size = 0, cur_max = MAX;
    
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
            if (deep < 4) {
                if (cur_size < cur_max) {
                    rec_dir[cur_size] = strdup(dd->d_name);
                    cur_size++;
                } else {
                    cur_max *= 2;
                    rec_dir = realloc(rec_dir, cur_max * sizeof(rec_dir[0]));
                    rec_dir[cur_size] = strdup(dd->d_name);
                    cur_size++;
                }
            }
        } else if (S_ISREG(buf.st_mode)) {
            if (access(str, R_OK) == 0 && buf.st_size <= max_size) {
                printf("%s\n", str + print_shift);
            }
        }
    }

    closedir(d);
    for (int i = 0; i < cur_size; i++) {
        char path_tmp[PATH_MAX + 1];
        snprintf(path_tmp, PATH_MAX, "%s/%s", path, rec_dir[i]);
        free(rec_dir[i]);
        rec_read(path_tmp, max_size, deep + 1, print_shift);
    }
    free(rec_dir);
}

int main(int argc, char **argv) {
    char *errptr;
    int max_size = (int)strtol(argv[2], &errptr, 10);
    if (errno || *errptr || errptr == argv[2] || (int)max_size != max_size) {
        return -1;
    }

    rec_read(argv[1], max_size, 1, strlen(argv[1]) + 1);
    
    return 0;
}
