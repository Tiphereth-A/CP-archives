#include <bits/stdc++.h>

#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
int n, a, b, c, d;
u64 pre, eve, odd;
inline bool even(int x) {
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    return x & 1;
}
inline u64 mod(u64 a, int m) { return (a < m) ? a : (a % m); }
int main() {
    scanf("%d%d%d%d%d%llu", &n, &a, &b, &c, &d, &pre);
    a %= d;
    b %= d;
    c %= d;
    _for(i, 1, n) even(pre = mod(mod((a * pre + b), d) * pre + c, d)) ? ++eve : ++odd;
    printf("%llu", eve * odd);
    return 0;
}