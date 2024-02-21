#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum
{
    SIZE = 100
};

int
main(int argc, char **argv)
{
    char buf[SIZE + 1];
    while (fgets(buf, SIZE + 1, stdin)) {
        double sum = 0;
        double x;

        int shift = 0;
        int cur_shift;

        while (sscanf(buf + shift, "%lf%n", &x, &cur_shift) == 2) {
            shift += cur_shift;
            sum += x;
        }

        printf("%lf\n", sum);
    }
}
