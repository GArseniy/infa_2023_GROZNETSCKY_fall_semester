// 8 сегм

struct seg
{
    int size;
    int base;
};

int
f(struct seg *table, int vaddr)
{
    int nseg = vaddr >> 29;
    int offset = (vaddr << 3) >> 3;
    if (table[nseg].size < offset) {
        return 25;
    }
    return table[nseg].base + offset;
}
