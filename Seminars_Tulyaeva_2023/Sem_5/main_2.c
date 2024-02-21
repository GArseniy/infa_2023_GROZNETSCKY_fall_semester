#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int
is_delete(char *str)
{
    if (access(str, W_OK)) {
        return 0;
    }
    unsigned long long len = strlen(str);
    return (str[len - 1] == '~' || ((len >= 4) && !strcmp(str + len - 2, ".back")));
}

int
main(int argc, char **argv)
{
    DIR *d = opendir(argv[1]);
    struct dirent *dd;

    char f_name[PATH_MAX];

    while ((dd = readdir(d))) {
        snprintf(f_name, PATH_MAX, "%s/%s", argv[1], dd->d_name);
        if (is_delete(f_name)) {
            unlink(f_name);
        }
    }

    closedir(d);
    return 0;
}
