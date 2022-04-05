#include <cstdio>
#define rg register
#define rgi register int
#define il inline
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (register int i = (r); i >= (l); --i)
#define gc getchar
#define tpn typename
template <tpn A>
inline A Max(const A &x, const A &y) {
    return x > y ? x : y;
}
template <tpn A>
inline void Swap(A &x, A &y) {
    x ^= y, y ^= x, x ^= y;
}
template <tpn A>
inline A Abs(const A &x) {
    return x > 0 ? x : -x;
}
#define N 105
int dep[N], f[11][N], wid[N];
int n, Nn = 1;
int ansd, answ;
int lca(int u, int v) {
    if (dep[u] > dep[v]) Swap(u, v);
    int dis = dep[v] - dep[u];
    fd(i, 10, 0) if ((1 << i) & dis) v = f[i][v];
    if (u == v) return u;
    fd(i, 10, 0) if (f[i][u] != f[i][v]) {
        u = f[i][u];
        v = f[i][v];
    }
    return f[0][u];
}
int main() {
    scanf("%d", &n);
    int tmp1, tmp2, tmpd;
    fp(i, 1, n - 1) {
        scanf("%d%d", &tmp1, &tmp2);
        f[0][tmp2] = tmp1;
        ansd = Max(ansd, tmpd = dep[tmp2] = dep[tmp1] + 1);
        answ = Max(answ, ++wid[tmpd]);
    }
    fp(i, 1, n) for (rgi j = 1; (1 << j) <= dep[i]; ++j) f[j][i] = f[j - 1][f[j - 1][i]];
    scanf("%d%d", &tmp1, &tmp2);
    int tmp3 = lca(tmp1, tmp2);
    printf("%d\n%d\n%d\n", ansd + 1, answ, dep[tmp1] * 2 + dep[tmp2] - dep[tmp3] * 3);
    return 0;
}