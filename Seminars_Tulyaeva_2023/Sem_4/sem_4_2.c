#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int
my_access(const char *fname, int mode)
{
    struct stat buf;
    if (stat(fname, &buf)) {
        return -1;
    }
    int user = get_uid();
    if (!user) {
        return 0;
    }
    unsigned short a = buf.st_mode;
    int shift = 0;
    if (user == buf.st_uid) {
        shift = 6;
    } else if (get_) {
    }
}

int
main(int argc, char **argv)
{
    return 0;
}
