#include <stdio.h>
#include <string.h>
#include "random_source.h"
#include <errno.h>
#include <stdlib.h>
#include <dlfcn.h>
enum
{
    BASE = 10,
};

char const randlinear_name[] = "linear";
char const randrand_name[] = "random";

void
error_report(long long error, const char *modulename)
{
    if (errno) {
        fprintf(stderr, "%s: Error! %s!\n", modulename, strerror(errno));
        exit(1);
    }
    if (!error) {
        fprintf(stderr, "%s: Error! Not enough memory!\n", modulename);
        exit(1);
    }
}

int
main(int argc, char *argv[])
{
    RandomSource *rr;
    char *handle = dlopen(NULL, RTLD_LAZY);
    if (strcmp(randlinear_name, argv[1]) == 0) {
        cast_random_factory random_factory = (cast_random_factory) dlsym(handle, "random_linear_factory");
        rr = (random_factory) (argv[3]);
    } else if (strcmp(randrand_name, argv[1]) == 0) {
        cast_random_factory random_factory = (cast_random_factory) dlsym(handle, "random_random_factory");
        rr = (random_factory) (NULL);

    } else {
        fprintf(stderr, "%s: Error! Invalid generator name!\n", argv[0]);
        exit(1);
    }

    char *endptr = NULL;
    long num_values = strtol(argv[2], &endptr, BASE);
    if (errno || *endptr || endptr == argv[2] || (int) num_values != num_values) {
        fprintf(stderr, "main: Oh no! You've entered something other than the number!\n");
        exit(1);
    }
    for (int i = 0; i < num_values; ++i) {
        printf("%.10g\n", (rr->ops->next)(rr));
    }
    rr->ops->destroy(rr);
    dlclose(handle);
    return 0;
}
