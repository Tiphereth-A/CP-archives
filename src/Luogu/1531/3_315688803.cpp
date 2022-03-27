#include <cstdio>
#include <iostream>
#define MAXN 200005LL
#define fp(i, l, r) for (register int(i) = (l); (i) <= (r); (i)++)
#define fd(i, l, r) for (register int i = l; i >= r; --i)
#define il inline
int a[MAXN << 2], t[MAXN << 2];
int n, N = 1, m;
il int Max(int a, int b) { return a > b ? a : b; }
il void build() {
    fp(i, 1, n) t[N + i] = a[i];
    fd(i, N - 1, 1) t[i] = Max(t[i << 1], t[i << 1 | 1]);
}
il void modify(int x, int k) {
    for (int i = N + x; i; i >>= 1) t[i] = Max(t[i], k);
}
il int query(int x, int y) {
    int ans = 0;
    for (int s = N + x - 1, r = N + y + 1; s ^ r ^ 1; s >>= 1, r >>= 1) {
        if (~s & 1) ans = Max(ans, t[s ^ 1]);
        if (r & 1) ans = Max(ans, t[r ^ 1]);
    }
    return ans;
}
int main() {
    scanf("%d%d", &n, &m);
    while (N < n + 2) N <<= 1;
    fp(i, 1, n) scanf("%d", a + i);
    build();
    while (m--) {
        char c;
        int x, y;
        std::cin >> c >> x >> y;
        if (c == 'Q')
            printf("%d\n", query(x, y));
        else
            modify(x, y);
    }
    return 0;
}