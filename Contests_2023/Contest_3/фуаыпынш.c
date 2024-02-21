#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

enum
{
    MAX_LEN = 15
};

struct Elem
{
    struct Elem *next;
    char *str;
};

struct Elem *
dup_elem(struct Elem *head)
{
    if (!head) {
        return head;
    }

    struct Elem *help = head;

    while (help) {
        if (!help->str) {
            help = help->next;
            continue;
        }

        char *p;
        errno = 0;
        long n = strtol(help->str, &p, 10);

        if (errno || *p || p == help->str || (int) n != n || n == INT_MAX) {
            help = help->next;
            continue;
        }

        struct Elem *node = (struct Elem *) calloc(1, sizeof(struct Elem));

        if (!node) {
            return NULL;
        }

        node->next = help->next;
        node->str = help->str;

        help->next = node;
        help->str = (char *) calloc(MAX_LEN, sizeof(char));

        if (!help->str) {
            return NULL;
        }

        snprintf(help->str, MAX_LEN, "%ld", n + 1);

        help = help->next->next;
    }

    return head;
}