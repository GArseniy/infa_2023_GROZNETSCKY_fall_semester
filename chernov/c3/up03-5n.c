/*
    Элемент списка определяется следующим образом:

    struct Elem {
        struct Elem *next;
        char *str;
    };

    str указывает на строку, размещенную в области динамической памяти.

    Напишите функцию на Си:

    struct Elem *dup_elem(struct Elem *head);

    Если у некоторого элемента p в строке p->str записано текстовое десятичное представление 32-битного целого числа x,
    причем пробелы в начале допускаются, а в конце - нет, то перед каждым таким элементом в список добавляется новый элемент,
    у которого в строке записано десятичное представление числа x + 1, если оно представимо 32-битным целым знаковым значением.
    В текстовом представлении числа в новом элементе списка не должно быть пробелов, лишних знаков плюс и нулей.

    Функция должна вернуть указатель на первый элемент получившегося списка.
*/

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

struct Elem
{
    struct Elem *next;
    char *str;
};

struct Elem *dup_elem(struct Elem *head) {
    if (head == NULL) {
        return NULL;
    }

    struct Elem *prev = NULL, *res = head;
    int flag = 0;
    while (head != NULL) {
        char *eptr = NULL;
        errno = 0;
        long x = strtol(head->str, &eptr, 10);
        if (errno || *eptr || eptr == head->str || (int)x != x || x == INT_MAX) {
            // skip
        } else {
            if (!flag) {
                res = calloc(1, sizeof(struct Elem));
                res->next = head;
                asprintf(&(res->str), "%ld", x + 1);
            } else {
                prev->next = calloc(1, sizeof(struct Elem));
                prev->next->next = head;
                asprintf(&(prev->next->str), "%ld", x + 1);
            }
        }

        flag = 1;
        prev = head;
        head = head->next;
    }

    return res;
}