/*
 Напишите программу, которая во втором каталоге найдет клоны файлов из первого каталога. Под клоном файла понимаются
 другие имена исходного файла или симлинки на исходный файл или другие имена исходного файла.

 В аргументах командной строки передаются пути к двум каталогам. На стандартный поток вывода напечатайте суммарный размер
 тех регулярных файлов из первого каталога, которые могут быть модифицированы текущим пользователем, и клон которого под тем же
 самым именем находятся во втором каталоге. При этом симлинки в первом каталоге игнорируются, но во втором каталоге файл с тем же
 самым именем может быть и симлинком на файл в первом каталоге.
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

int main(int argc, char **argv) {
    DIR *dir1 = opendir(argv[1]);
    if (dir1 < 0) {
        return -1;
    }
    DIR *dir2 = opendir(argv[2]);
    if (dir2 < 0) {
        return -1;
    }
    
    unsigned long long res = 0; 
    struct dirent *dd;
    while ((dd = readdir(dir1)) != NULL) {
        char path1[PATH_MAX + 1];
        snprintf(path1, PATH_MAX, "%s/%s", argv[1], dd->d_name);
        struct stat buf;
        if (lstat(path1, &buf) < 0) {
            continue;
        }
        
        if (!S_ISREG(buf.st_mode) || access(path1, W_OK) != 0) {
            continue;
        }
        
        seekdir(dir2, 0);
        
        struct dirent *dd2;
        while ((dd2 = readdir(dir2)) != NULL) {
            char path2[PATH_MAX + 1];
            snprintf(path2, PATH_MAX, "%s/%s", argv[2], dd2->d_name);
            struct stat buf1;
            
            if (stat(path2, &buf1) < 0) {
                continue;
            }
            
            if (buf1.st_ino == buf.st_ino && buf1.st_dev == buf.st_dev) {
                res += buf.st_size;
                break;
            }
        }
    }
    
    printf("%lld\n", res);
}
