#include <cmath>
#include <cstdio>
#define rgi register int
#define il inline
#define _fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define tpn typename
#define _lowbit(x) (1 << __builtin_ctz(x))
typedef long long i64;
template <tpn A>
inline void Swap(A &x, A &y) { x ^= y ^= x ^= y; }
const int N = 1e5 + 5;
int n, m;
i64 a[N], tree[N << 2], fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
il void mdf(int x, i64 k) {
    for (int i = x; i <= n; i += _lowbit(i)) tree[i] += k;
}
il i64 qry(int x) {
    i64 res = 0;
    for (int i = x; i; i -= _lowbit(i)) res += tree[i];
    return res;
}
int main() {
    scanf("%d", &n);
    _fp(i, 1, n) {
        scanf("%lld", a + i);
        fa[i] = i;
        mdf(i, a[i]);
    }
    scanf("%d", &m);
    fa[n + 1] = n + 1;
    int o, x, tmp, y;
    while (m--) {
        scanf("%d%d%d", &o, &x, &y);
        if (x > y) Swap(x, y);
        if (o)
            printf("%lld\n", qry(y) - qry(x - 1));
        else
            for (rgi i = x; i <= y;) {
                mdf(i, (tmp = sqrt(a[i])) - a[i]);
                fa[i] = ((a[i] = tmp) <= 1) ? i + 1 : i;
                i = (find(i) == i) ? i + 1 : fa[i];
            }
    }
    return 0;
}