/*
 В аргументах командной строки задается путь к каталогу.

 На стандартный поток вывода напечатайте количество файлов в заданном каталоге
 (без подкаталогов), удовлетворяющих следующему условию:

    Файл регулярный.
    Файл доступен на выполнение текущему пользователю.
    Его имя заканчивается на суффикс .exe.

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        return -1;
    }

    DIR *d = opendir(argv[1]);
    int cnt = 0;
    struct dirent *dd;
    while ((dd = readdir(d)) != NULL) {
        char path[PATH_MAX + 1];
        snprintf(path, PATH_MAX, "%s/%s", argv[1], dd->d_name);

        struct stat buf;
        if (stat(path, &buf) < 0) {
            continue;
        }

        int len = strlen(dd->d_name);
        if (len < 4) {
            continue;
        }

        if (S_ISREG(buf.st_mode) && strcmp(dd->d_name + len - 4, ".exe\0") == 0 && !access(path, X_OK)) {
            cnt++;
        }
    }
    
    printf("%d\n", cnt);
}
