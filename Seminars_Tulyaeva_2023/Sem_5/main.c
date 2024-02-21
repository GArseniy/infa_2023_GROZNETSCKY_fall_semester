#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

unsigned long long
size_of_file(char *str)
{
    struct stat buf;
    return (!lstat(str, &buf) && S_ISREG(buf.st_mode)) ? buf.st_size : 0;
}

int
main(int argc, char **argv)
{
    DIR *d = opendir(argv[1]);
    struct dirent *dd;

    unsigned long len = PATH_MAX;
    char *f_name = calloc(len, sizeof(char));

    unsigned long long sum = 0;
    while ((dd = readdir(d))) {
        snprintf(f_name, len, "%s/%s", argv[1], dd->d_name);
        sum += size_of_file(f_name);
    }

    printf("%llu\n", sum);
    closedir(d);
    return 0;
}
