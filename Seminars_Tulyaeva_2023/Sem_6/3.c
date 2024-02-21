#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int
main(int argc, char **argv)
{
    DIR *d = opendir(argv[1]);
    struct dirent *dd;

    char f_name[PATH_MAX];

    while ((dd = readdir(d))) {
        snprintf(f_name, PATH_MAX, "%s/%s", argv[1], dd->d_name);
        struct stat buf;
        lstat(f_name, &buf);

        __time_t now = time(NULL);
        if (S_ISREG(buf.st_mode) && (now - buf.st_mtime) <= 2 * 7 * 24 * 60 * 60) {
            char new_file[PATH_MAX];
            snprintf(new_file, PATH_MAX, "%s/%s", argv[2], dd->d_name);
        }
    }

    closedir(d);
    return 0;
}
