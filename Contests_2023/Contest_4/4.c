#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int32_t
convert(const unsigned char *buf)
{
    int32_t ret = 0;
    for (int i = 0; i < sizeof(ret); ++i) {
        ret |= buf[i] << (sizeof(ret) - i - 1) * CHAR_BIT;
    }
    return ret;
}

void
print_tree(int fd, int32_t node_id)
{
    enum
    {
        CNT_FIELDS = 3,
        SIZEOF_INT = sizeof(node_id),
        SIZEOF_NODE = CNT_FIELDS * SIZEOF_INT
    };

    unsigned char node[SIZEOF_NODE];
    if (pread(fd, &node, sizeof(node), node_id * SIZEOF_NODE) != sizeof(node)) {
        return;
    }

    int32_t buf;
    if ((buf = convert(node + SIZEOF_INT * 2))) {
        print_tree(fd, buf);
    }
    printf("%d ", convert(node));
    if ((buf = convert(node + SIZEOF_INT * 1))) {
        print_tree(fd, buf);
    }
}

int
main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }

    print_tree(fd, 0);
    printf("\n");

    close(fd);
    return 0;
}