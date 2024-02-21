/*
 В аргументах командной строки передаются пути к файлам.

 Если в списке путей к файлам несколько раз встречается один и тот же файл, то оставьте из этих путей один лексикографически
 максимальный (в смысле сравнения строк) путь. Все оставшиеся (то есть уникальные) пути выведите на стандартный поток вывода в
 порядке лексикографического возрастания по одному пути на строку.

 Если информация о файле по указанному пути недоступна, такой путь игнорируется и вывод не попадает.

 Два пути являются путями к одному и тому же файлу, если либо один из них является символической ссылкой на другой,
 либо оба из них являются символическими ссылками на третий файл, либо файлы являются жесткими ссылками друг друга,
 либо пути равны.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

void print_res(char **res, int n) {
    for (int i = 0; i < n; i++) {
        puts(res[i]);
    }
}

int cmp(const void *s1, const void *s2) {
    return strcmp(*(char **)s1, *(char **)s2);
}

int main(int argc, char **argv) {
    char **res = calloc(argc, sizeof(res[0]));
    int cur_i = 0;

    for (int i = 1; i < argc; i++) {
        int flag = 1;
        struct stat cur;
        if (stat(argv[i], &cur) < 0) {
            continue;
        }

        for (int j = 0; j < cur_i; j++) {
            struct stat saved; 
            if (stat(res[j], &saved) < 0) {
                continue;
            }

            if (cur.st_ino == saved.st_ino && cur.st_dev == saved.st_dev) {
                if (strcmp(argv[i], res[j]) > 0) {
                    res[j] = argv[i];
                }

                flag = 0;
                break;
            }
        }

        if (flag) {
            res[cur_i++] = argv[i];
        }
    }

    qsort(res, cur_i, sizeof(res[0]), cmp);

    print_res(res, cur_i);

    free(res);

    return 0;
}
