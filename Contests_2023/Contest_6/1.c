#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int
is_correct(const char *f_name)
{
    char ext[] = ".exe";
    enum
    {
        LEN_OF_EXT = sizeof(ext) - 1
    };

    struct stat buf;
    unsigned long len;

    return (!stat(f_name, &buf) && S_ISREG(buf.st_mode) && (len = strlen(f_name)) >= LEN_OF_EXT &&
            !strcmp(&f_name[len - LEN_OF_EXT], ext) && !access(f_name, X_OK));
}

int
main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }

    DIR *d = opendir(argv[1]);
    if (!d) {
        return 1;
    }

    struct dirent *dd;
    char f_name[PATH_MAX];
    unsigned long long cnt_of_correct = 0;

    while ((dd = readdir(d))) {
        if (snprintf(f_name, sizeof(f_name), "%s/%s", argv[1], dd->d_name) < sizeof(f_name)) {
            cnt_of_correct += is_correct(f_name);
        }
    }

    printf("%llu\n", cnt_of_correct);
    closedir(d);
    return 0;
}
