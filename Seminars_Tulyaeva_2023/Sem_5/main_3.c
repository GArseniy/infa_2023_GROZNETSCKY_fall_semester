#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int
is_empty_dir(char *dir_name)
{
    unsigned long len = strlen(dir_name);
    if (((len >= 3) && !strcmp(&dir_name[len - 3], "/..")) || ((len >= 2 && !strcmp(&dir_name[len - 2], "/.")))) {
        return 0;
    }

    DIR *d = opendir(dir_name);

    unsigned long long count = 0;
    while (readdir(d)) {
        ++count;
    }

    return count == 2;
}

int
main(int argc, char **argv)
{
    DIR *d = opendir(argv[1]);
    struct dirent *dd;

    char f_name[PATH_MAX];

    while ((dd = readdir(d))) {
        snprintf(f_name, PATH_MAX, "%s/%s", argv[1], dd->d_name);
        if (is_empty_dir(f_name)) {
            rmdir(f_name);
        }
    }

    closedir(d);
    return 0;
}
