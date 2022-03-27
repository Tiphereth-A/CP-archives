#include <algorithm>
#include <cstdio>
#define il inline
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define tpn typename
template <tpn A>
inline A Max(const A& x, const A& y) {
    return x > y ? x : y;
}
template <tpn A>
inline void read(A& x) {
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
il int lis(int f, int l) {
    int g[N] = {0};
    int len = 1;
    if (f < l) {
        g[1] = a[f];
        fp(i, f, l) {
            if (a[i] > g[len])
                g[++len] = a[i];
            else {
                int j = std::lower_bound(g + 1, g + len + 1, a[i]) - g;
                g[j] = a[i];
            }
        }
    } else if (f > l) {
        g[1] = a[l];
        fd(i, f, l) {
            if (a[i] > g[len])
                g[++len] = a[i];
            else {
                int j = std::lower_bound(g + 1, g + len + 1, a[i]) - g;
                g[j] = a[i];
            }
        }
    }
    return len;
}
int main() {
    read(n);
    fp(i, 1, n) read(a[i]);
    fp(i, 1, n) {
        f[i] = lis(1, i) + lis(n, i) - 1;
        maxn = Max(maxn, f[i]);
    }
    printf("%d", n - maxn);
    return 0;
}