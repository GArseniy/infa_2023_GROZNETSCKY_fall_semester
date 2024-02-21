int satsum(int a, int b) {
    int MAX = ~0u >> 1;
    int MIN = ~MAX;
    if ((a > 0) && (b > MAX - a)) {
        return MAX;
    }
    if ((a < 0) && (b < MIN - a)) {
        return MIN;
    }
    return a + b;
}


int cnt_bit(int a) {
    unsigned u = (unsigned) a;
    int cnt = 0;

    while ((u)) {
        cnt += (u & 1);
        u >>= 1;
    }

    return cnt;
}

int main(void) {

    return 0;
}
