int
size_of_file(int n, int *table)
{
    int num = n;
    int ret = 0;

    while (num) {
        num = table[num];
        ++ret;
    }
    return ret;
}