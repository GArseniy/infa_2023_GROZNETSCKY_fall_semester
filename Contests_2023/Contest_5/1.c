#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum
{
    BASE = 1024
};

unsigned long long
size_of_file(char *str)
{
    struct stat buf;
    return (!lstat(str, &buf) && S_ISREG(buf.st_mode) && !(buf.st_size % BASE) && buf.st_nlink == 1) ? buf.st_size : 0;
}

int
main(int argc, char **argv)
{
    unsigned long long size_of_files = 0;
    for (int i = 1; i < argc; ++i) {
        size_of_files += size_of_file(argv[i]);
    }
    printf("%llu\n", size_of_files);
    return 0;
}
