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

void print_struct(struct Elem *head) {
    while (head) {
        printf("'%s'\n", head->str);
        head = head->next;
    }
}

int main(void) {
    struct Elem elem1;
    // elem1.str = NULL;
    elem1.str = calloc(10, sizeof(elem1.str[0]));
    elem1.str[0] = '1';

    struct Elem elem2;
    elem2.str = calloc(10, sizeof(elem2.str[0]));
    elem2.str[0] = 'a';

    struct Elem elem3;
    elem3.str = calloc(10, sizeof(elem3.str[0]));
    elem3.str[1] = '2';
    elem3.str[2] = '0';
    elem3.str[0] = ' ';

    struct Elem elem4;
    elem4.str = calloc(10, sizeof(elem4.str[0]));
    elem4.str[0] = '-';
    elem4.str[1] = '0';
    elem4.str[2] = '3';

    struct Elem elem5;
    elem5.str = calloc(10, sizeof(elem5.str[0]));
    elem5.str[0] = '0';
    elem5.str[1] = '0';
    elem5.str[2] = '0';

    struct Elem elem6;
    elem6.str = calloc(10, sizeof(elem6.str[0]));
    elem6.str[0] = '-';
    elem6.str[1] = '0';
    elem6.str[2] = '1';

    struct Elem *head = &elem1;
    elem1.next = &elem2;
    elem2.next = &elem3;
    elem3.next = &elem4;
    elem4.next = &elem5;
    elem5.next = &elem6;
    elem6.next = NULL;

    struct Elem *res = dup_elem(head);
    print_struct(res);

    free(elem1.str);
    free(elem2.str);
    free(elem3.str);
    free(elem4.str);
}
