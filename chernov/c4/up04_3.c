/*
    В аргументах командной строки задается имя входного бинарного файла произвольного доступа. Бинарный файл рассматривается
    как массив структур:

    struct Node {
        int32_t key;
        int32_t left_idx;
        int32_t right_idx;
    };

    Структура описывает вершину бинарного дерева поиска, где key – ключ поиска, а значения
    left_idx и right_idx – индексы в массиве соответственно левой и правой вершины.
    Корень дерева находится в элементе массива с индексом 0. Признаком отсутствия соответствующего поддерева
    в вершине является индекс, равный 0.

    Числа в файле хранятся в естественном для x86 представлении (little-endian).

    На стандартный поток вывода напечатайте ключи, размещенные в данном дереве, в порядке убывания. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

enum
{
    STRUCT_SIZE = 12
};

void print_tree(struct Node *arr, struct Node head) {
    if (head.right_idx != 0) {
        print_tree(arr, arr[head.right_idx]);
    }

    printf("%d ", head.key);

    if (head.left_idx != 0) {
        print_tree(arr, arr[head.left_idx]);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }

    int size_file = lseek(fd, 0, SEEK_END);
    struct Node *arr = calloc(size_file / STRUCT_SIZE, STRUCT_SIZE);
    if (arr == NULL) {
        return 1;
    }

    if (lseek(fd, 0, SEEK_SET) < 0) {
        return 1;
    }

    int i = 0;
    while (read(fd, &(arr[i]), sizeof(arr[i])) == sizeof(arr[i])) {
        i++;
    }

    print_tree(arr, arr[0]);
    printf("\n");

    free(arr);
}
