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

#include "stdio.h"
int
main()
{
    char str[] = "/a/aa/../././aaaaaa/aaaaaaaaaaa/a/aaaaa/aa/aaaaaaa/a/../aaa/../../aa";
    normalize_path(str);

    printf("%s\n", str);

    return 0;
}