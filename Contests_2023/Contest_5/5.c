#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum
{
    SIZE_OF_CUR_DIR = 2,
    SIZE_OF_PAR_DIR = 3,
};

void
skip(char *str, int size)
{
    for (int i = 0; (str[i] = str[i + size]); ++i) {
    }
}

int
offset_dir(const char *str)
{
    int offset;
    for (offset = 1; str[-offset] != '/'; ++offset) {
    }
    return offset;
}

void
end_proc(char *str, int i)
{
    if (i == 0) {
        str[0] = '/';
        str[1] = 0;
        return;
    }

    if (i == 1) {
        return;
    }

    if (str[i - 1] == '/') {
        str[i - 1] = 0;
        return;
    }
}

void
normalize_path(char *buf)
{
    if (!buf || buf[0] != '/') {
        return;
    }

    int i = 0;
    while (buf[i]) {
        if (buf[i] != '/') {
            ++i;
            continue;
        }

        if (buf[i + 0] == '/' && buf[i + 1] == '.' && (buf[i + 2] == '/' || buf[i + 2] == 0)) {
            skip(&buf[i], SIZE_OF_CUR_DIR);
            continue;
        }

        if (buf[i + 0] == '/' && buf[i + 1] == '.' && (buf[i + 2] == '.') && (buf[i + 3] == '/' || buf[i + 3] == 0)) {
            int offset = (i > 0) ? offset_dir(&buf[i]) : 0;
            skip(&buf[i -= offset], offset + SIZE_OF_PAR_DIR);
            continue;
        }

        ++i;
    }

    end_proc(buf, i);
}

unsigned long long
is_equal_dir(const char *s1, const char *s2)
{
    unsigned long long offset;
    for (offset = 0; *s1 && *s2; ++s1, ++s2, ++offset) {
        if (*s1 != *s2) {
            return 0;
        }
        if (*s1 == '/' && offset) {
            return offset;
        }
    }
    return offset;
}

char *
relativize_path(const char *path1, const char *path2)
{
    if (path1 == NULL || path2 == NULL) {
        return NULL;
    }

    char *norm1 = strdup(path1);
    char *norm2 = strdup(path2);

    char *iter1 = norm1;
    char *iter2 = norm2;

    normalize_path(iter1);
    normalize_path(iter2);

    char *const ret_str = calloc((strlen(iter1) + strlen(iter2)) * 2, sizeof(char));

    unsigned long long offset;
    while ((offset = is_equal_dir(iter1, iter2)) && iter1[offset]) {
        iter1 += offset;
        iter2 += offset;
    }

    unsigned long long iter = 0;
    while (*(++iter1)) {
        if (*iter1 == '/') {
            ret_str[iter++] = '.';
            ret_str[iter++] = '.';
            ret_str[iter++] = '/';
        }
    }

    iter2 += *(iter2) == '/';

    while (*(iter2)) {
        ret_str[iter++] = *iter2++;
    }

    if (!iter) {
        ret_str[iter++] = '.';
    }

    if (ret_str[--iter] != '/') {
        ++iter;
    }

    ret_str[iter++] = 0;

    free(norm1);
    free(norm2);

    return ret_str;
}

int
main(void)
{
    const char str1[] = "/a";
    const char str2[] = "/";

    printf("%s\n", relativize_path(str1, str2));

    return 0;
}