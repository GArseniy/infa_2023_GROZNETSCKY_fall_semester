#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

void
ivan_del(char *buf, int n)
{
    int cur = n;
    while (buf[cur] != '\0') {
        buf[cur] = buf[cur + 1];
        cur++;
    }
}

void
ivan_normalize_path(char *buf)
{
    if (buf[0] == '/' && buf[1] == '\0') {
        return;
    }

    int cur = 1;
    while (buf[cur] != '\0') {
        if (!cur || buf[cur - 1] != '/') {
            cur++;
            continue;
        }

        if (buf[cur] != '\0' && buf[cur + 1] != '\0') {
            if (buf[cur] == '.' && buf[cur + 1] == '.' && (buf[cur + 2] == '/' || buf[cur + 2] == '\0')) {

                for (int i = 0; i < 3; i++) {
                    ivan_del(buf, cur);
                }

                cur--;
                if (cur) {
                    ivan_del(buf, cur--);
                    while (buf[cur] != '/') {
                        ivan_del(buf, cur--);
                    }
                } else {
                    continue;
                }
            } else if (buf[cur] == '.' && buf[cur + 1] == '/') {
                ivan_del(buf, cur);
                ivan_del(buf, cur--);
            }
        } else if (buf[cur] == '.' && buf[cur + 1] == '\0') {
            ivan_del(buf, cur--);
        }
        cur++;
    }

    if (!(buf[0] == '/' && buf[1] == '\0') && buf[cur - 1] == '/') {
        ivan_del(buf, cur - 1);
    }
}

char *
ivan_relativize_path(const char *path1, const char *path2)
{
    char *norm1 = strdup(path1);
    char *norm2 = strdup(path2);
    ivan_normalize_path(norm1);
    ivan_normalize_path(norm2);

    unsigned long long el = 0;
    char *prev1 = norm1;
    char *prev2 = norm2;

    while (norm1[el] == norm2[el] && norm2[el] > 0) {
        if (norm1[el] == '/') {
            prev1 = norm1 + el;
            prev2 = norm2 + el;
        }
        el++;
    }

    char *cur = NULL;
    char *res = calloc((strlen(norm1) + strlen(norm2)) * 2, sizeof(*res));
    if (norm2[el] == 0 && strchr(prev1 + 1, '/')) {
        if (norm2[1] == 0) {
            strcpy(res, "../");
        }
        cur = strchr(prev1 + 1, '/');
        prev1 = cur;
        while ((cur = strchr(prev1 + 1, '/'))) {
            strcat(res, "../");
            prev1 = cur;
        }
        if (strlen(res) > 0) {
            res[strlen(res) - 1] = '\0';
        }
    } else {
        while ((cur = strchr(prev1 + 1, '/'))) {
            strcat(res, "../");
            prev1 = cur;
        }
        strcpy(res + strlen(res), prev2 + 1);
    }

    if (res[0] == 0) {
        res[0] = '.';
    }

    free(norm1);
    free(norm2);

    return res;
}