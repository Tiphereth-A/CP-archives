#include <cstdio>
#define N 500005
#define fd(i, r, l) for (register int(i) = (r); (i) >= (l); --(i))
#define il inline
struct edge {
    int to, nxt;
} e[N << 1];
int head[N], tot, f[21][N], dep[N], lg[N];
bool flag[N];
il void Swap(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}
il void add(int x, int y) {
    e[++tot].to = y;
    e[tot].nxt = head[x];
    head[x] = tot;
}
void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    f[0][x] = fa;
    for (int i = 1; (1 << i) <= dep[x]; ++i)
        f[i][x] = f[i - 1][f[i - 1][x]];
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v != fa)
            dfs(v, x);
    }
}
il int lca(int x, int y) {
    if (dep[x] < dep[y])
        Swap(x, y);
    while (dep[x] > dep[y])
        x = f[lg[dep[x] - dep[y]] - 1][x];
    if (x == y) return x;
    fd(i, lg[dep[x]], 0) if (f[i][x] != f[i][y]) {
        x = f[i][x];
        y = f[i][y];
    }
    return f[0][x];
}
int main() {
    int n, m, s, x, y;
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n - 1; ++i) {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    }
    dfs(s, 0);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        printf("%d\n", lca(x, y));
    }
    return 0;
}