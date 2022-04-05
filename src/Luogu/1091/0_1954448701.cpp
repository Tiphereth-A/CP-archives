#include <algorithm>
#include <cstdio>
#define il inline
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define tpn typename
template <tpn A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <tpn A>
inline void read(A &x) {
    char c;
    A neg = 1;
    do {
        c = getchar();
    } while ((c < '0' || c > '9') && c != '-');
    if (c == '-') neg = -1, c = getchar();
    x = 0;
    do {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    } while (c >= '0' && c <= '9');
    x *= neg;
}
const int M = 100005;
const int N = 105;
const int INF = 0x7fffffff;
int n, a[N], f[N], g[N], maxn;
int main() {
    read(n);
    fp(i, 1, n) read(a[i]);
    fp(i, 1, n) fp(j, 0, i - 1) if (a[i] > a[j]) f[i] = Max(f[i], f[j] + 1);
    fd(i, n, 1) fd(j, n + 1, i + 1) if (a[i] > a[j]) g[i] = Max(g[i], g[j] + 1);
    fp(i, 1, n) maxn = Max(maxn, f[i] + g[i] - 1);
    printf("%d", n - maxn);
    return 0;
}