#include <cstdio>
#define il inline
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
typedef unsigned long long u64;
int n, a, b, c, d;
u64 pre, cnt[2];
int main() {
    scanf("%d%d%d%d%d%llu", &n, &a, &b, &c, &d, &pre);
    a %= d;
    b %= d;
    c %= d;
    _fp(i, 1, n) cnt[__builtin_popcount(pre = (((a * pre + b) % d * pre + c) % d)) & 1]++;
    printf("%llu", cnt[0] * cnt[1]);
    return 0;
}