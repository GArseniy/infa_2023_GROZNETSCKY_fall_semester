#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <gnu/lib-names.h>
#include <errno.h>

enum
{
    BASE = 10,
    SIGNATURE_I = 3
};

union Arguments
{
    char arg[64];
};

int main(int argc, char **argv) {
    int len_sig = strlen(argv[SIGNATURE_I]);
    union Arguments arg = {};

    int k = SIGNATURE_I + 1, shift = 0;

    for (int i = 1; i < len_sig; i++) {
        switch (argv[SIGNATURE_I][i]) {
            case 's':
                char *s = argv[k];
                memcpy(arg.arg + shift, &s, sizeof(s));
                shift += sizeof(s);
                k++;
                break;
            case 'd':
                char *eptr = NULL;
                errno = 0;
                double x = strtod(argv[k], &eptr);
                if (errno || *eptr || argv[k] == eptr || (double) x != x) {
                    exit(1);
                }

                memcpy(arg.arg + shift, &x, sizeof(x));
                shift += sizeof(x);
                k++;
                break;
            case 'i':
                eptr = NULL;
                errno = 0;
                int y = (int)strtol(argv[k], &eptr, BASE);
                if (errno || *eptr || argv[k] == eptr) {
                    exit(1);
                }

                memcpy(arg.arg + shift, &y, sizeof(y));
                shift += sizeof(y);
                k++;
                break;
        }
    }

    void *handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        exit(1);
    }

    void *func = dlsym(handle, argv[2]);

    switch (argv[SIGNATURE_I][0]) {
        case 'v':
            ((void (*) (union Arguments))(func))(arg);
            break;
        case 'd':
            printf("%.10g\n", (((double (*) (union Arguments))(func))(arg)));
            break;
        case 'i':
            printf("%d\n", (((int (*) (union Arguments))(func))(arg)));
            break;
        case 's':
            printf("%s\n", (((char* (*) (union Arguments))(func))(arg)));
            break;
    }

    if (dlclose(handle) != 0) {
        exit(1);
    }

    return 0;
}
