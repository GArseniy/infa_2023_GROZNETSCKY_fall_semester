#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int
main(void)
{
    int fd = open("test.bin", O_RDWR | O_TRUNC | O_CREAT, 0777);

    int n;
    printf("Count of elems:\n");
    scanf("%d", &n);

    int type;
    printf("Int (1) / Double (2) / Long Long (3)  / Char (4)\n");
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
            scanf("%ff", &c);
            write(fd, &c, sizeof(c));
        }

        break;

    case 3:
        for (int i = 0; i < n; ++i) {
            long long c;
            scanf("%dd", &c);
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
