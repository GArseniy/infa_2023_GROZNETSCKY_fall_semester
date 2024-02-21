
char *DISKS[4];
int fd[4];

void
init(char **d)
{
    for (int i = 0; i < 4; ++i) {
        fd[0] = open(DISKS[0], O_RDWR);
    }
}

void
f(int num, char *buf)
{
    int offset = num / 4;
    int disk = fd[num % 4];

    pread(disk, buf, BLOCK_SIZE, offset * BLOCK_SIZE);
}
