#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }
    int fd = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, 0777);

    int n;
    scanf("%d", &n);

    int type;
    scanf("%d", &type);

    switch (type) {
    case 1:
        for (int i = 0; i < n; ++i) {
            int c;
            scanf("%d", &c);
            write(fd, &c, sizeof(c));
        }

        break;

    case 2:
        for (int i = 0; i < n; ++i) {
            double c;
            scanf("%lf", &c);
            write(fd, &c, sizeof(c));
        }

        break;

    case 3:
        for (int i = 0; i < n; ++i) {
            long long c;
            scanf("%lld", &c);
            write(fd, &c, sizeof(c));
        }

        break;

    case 4:
        for (int i = 0; i < n; ++i) {
            char c;
            scanf("%c", &c);
            write(fd, &c, sizeof(c));
        }

        break;

    default:
        break;
    }

    close(fd);

    return 0;
}
