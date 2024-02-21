int
satsum(int a, int b)
{
    enum
    {
        MY_INT_MAX = ~0u >> !0,
        MY_INT_MIN = ~MY_INT_MAX
    };
    if ((a > 0) && (b > MY_INT_MAX - a)) {
        return MY_INT_MAX;
    }
    if ((a < 0) && (b < MY_INT_MIN - a)) {
        return MY_INT_MIN;
    }
    return a + b;
}
