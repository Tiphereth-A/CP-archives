#include <cstdio>
#include <ctime>
#include <iostream>
using namespace std;
const int maxn = 1e6 + 5;
int a[maxn];
struct Node {
    int l, r, val;
} hjt[maxn * 40];
int cnt, root[maxn];
void build(int l, int r, int &k) {
    k = ++cnt;
    if (l == r) {
        hjt[k].val = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(l, m, hjt[k].l);
    build(m + 1, r, hjt[k].r);
}
void modify(int l, int r, int pre, int &now, int p, int z) {
    hjt[now = ++cnt] = hjt[pre];
    if (l == r) {
        hjt[now].val = z;
        return;
    }
    int m = (l + r) >> 1;
    if (p <= m)
        modify(l, m, hjt[pre].l, hjt[now].l, p, z);
    else
        modify(m + 1, r, hjt[pre].r, hjt[now].r, p, z);
}
int query(int l, int r, int ver, int p) {
    if (l == r) return hjt[ver].val;
    int m = (l + r) >> 1;
    if (p <= m)
        return query(l, m, hjt[ver].l, p);
    else
        return query(m + 1, r, hjt[ver].r, p);
}
signed main(signed argc, char const *argv[]) {
    clock_t c1 = clock();
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    build(1, n, root[0]);
    for (int i = 1; i <= m; i++) {
        int ver, opt, p, z;
        scanf("%d%d%d", &ver, &opt, &p);
        if (opt == 1) {
            scanf("%d", &z);
            modify(1, n, root[ver], root[i], p, z);
        } else {
            printf("%d\n", query(1, n, root[ver], p));
            root[i] = root[ver];
        }
    }
end:
    cerr << "Time Used:" << clock() - c1 << "ms" << endl;
    return 0;
}