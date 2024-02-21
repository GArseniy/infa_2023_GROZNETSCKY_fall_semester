/*
    На стандартный поток вывода напечатайте суммарный размер файлов, удовлетворяющих одновременно следующим условиям:
    Файл существует и его размер равен целому числу кибибайт (2^10).
    Файл является регулярным, при этом не является символической ссылкой.
    Файл имеет единственное имя в файловой системе.
*/

#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


enum
{
    BASE = 1024
};

int main(int argc, char **argv) {
    unsigned long long res = 0;
    for (int i = 1; i < argc; i++) {
        struct stat buf;
        if (lstat(argv[i], &buf) < 0) {
            continue;
        }
        
        if (S_ISREG(buf.st_mode) && buf.st_nlink == 1 && buf.st_size % BASE == 0) {
            res += buf.st_size;
        }
    }
    
    printf("%llu\n", res);
}
