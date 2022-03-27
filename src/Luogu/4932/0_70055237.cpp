#include <cstdio>
#define il inline
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (register int i = (l); i < (r); ++i)
typedef unsigned long long u64;
int n, a, b, c, d;
u64 pre, eve, odd;
il bool even(int x) {
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    return x & 1;
}
il u64 mod(u64 a, int m) { return (a < m) ? a : (a % m); }
int main() {
    scanf("%d%d%d%d%d%llu", &n, &a, &b, &c, &d, &pre);
    a %= d;
    b %= d;
    c %= d;
    _fp(i, 1, n) even(pre = mod(mod(mod(pre * pre, d) * a, d) + mod(pre * b, d) + c, d)) ? ++eve : ++odd;
    printf("%llu", eve * odd);
    return 0;
}