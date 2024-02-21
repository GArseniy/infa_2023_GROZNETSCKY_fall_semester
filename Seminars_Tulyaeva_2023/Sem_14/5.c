struct seg
{
    int pid;
    int vp;
};

int
f(struct seg *table, int cnt, int Vaddr)
{
    pid_t pid = getpid();

    int offset = (Vaddr << 20) >> 20;
    int VP = Vaddr >> 12;

    int FP;
    for (FP = 0; FP < cnt; ++FP) {
        if (table[FP].pid == pid && table[FP].vp == VP) {
            return offset | (FP << 12);
        }
    }

    return NULL;
}