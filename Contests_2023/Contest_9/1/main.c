#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "random_source.h"

int
wrap_strtol(const char *str, int *x)
{
    if (!str) {
        return -1;
    }
    errno = 0;
    char *p = NULL;
    long n = strtol(str, &p, 10);
    if (errno || *p || p == str || (int) n != n) {
        errno = 0;
        return -1;
    }
    *x = (int) n;
    return 0;
}

enum config
{
    CNT_MODE = 2,
    MAX_STR = 32
};

const char modes[CNT_MODE][MAX_STR] = {"random", "linear"};
const char factory_names[CNT_MODE][MAX_STR] = {"random_random_factory", "random_linear_factory"};

int
main(int argc, char **argv)
{
    if (argc != 4) {
        return 1;
    }

    int mode = -1;
    for (int i = 0; i < CNT_MODE; ++i) {
        if (strcmp(argv[1], modes[i]) == 0) {
            mode = i;
            break;
        }
    }

    if (mode == -1) {
        return 1;
    }

    int cnt;
    if (wrap_strtol(argv[2], &cnt)) {
        return 1;
    }

    void *handle;
    RandomSource *(*random_factory)(const char *);
    char *error;
    handle = dlopen(NULL, RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        return 1;
    }
    random_factory = dlsym(handle, factory_names[mode]);
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    RandomSource *rr;
    rr = random_factory(argv[3]);

    for (int i = 0; i < cnt; ++i) {
        printf("%.10g\n", rr->ops->next(rr));
    }

    rr->ops->destroy(rr);

    dlclose(handle);

    return 0;
}
