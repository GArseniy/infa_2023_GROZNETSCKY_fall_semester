#include <stdlib.h>
#include <stdio.h>
#include "errno.h"
#include <limits.h>

enum
{
    BUF_SIZE = 15
};

struct Elem
{
    struct Elem *next;
    char *str;
};

int
wrap_strtol(char *str, int *x)
{
    if (!str) {
        return 0;
    }
    char *p = NULL;
    long n = strtol(str, &p, 10);
    if (errno || *p || p == str || (int) n != n) {
        errno = 0;
        return 0;
    }
    *x = n;
    return 1;
}

struct Elem *
dup_elem(struct Elem *head)
{
    if (!head) {
        return head;
    }
    int x;
    if (wrap_strtol(head->str, &x) && x != INT_MAX) {
        struct Elem *next = calloc(1, sizeof(*head));
        next->str = head->str;
        next->next = head->next;
        char *inc_str = calloc(BUF_SIZE, sizeof(x));
        sprintf(inc_str, "%d", x + 1);
        head->str = inc_str;
        head->next = next;
        dup_elem(next->next);
    } else {
        dup_elem(head->next);
    }
    return head;
}
