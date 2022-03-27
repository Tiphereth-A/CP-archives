#include <cstdio>
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define il inline
typedef long long ll;
#define MAXN 5000005
ll t[MAXN], a[MAXN], delta[MAXN];
int n, m;
il int lowbit(int n) { return n & (-n); }
il ll getsum(int x) {
    ll ans = 0;
    for (int i = x; i > 0; i -= lowbit(i)) ans += t[i];
    return ans;
}
il void modify(int x, int k) {
    for (int i = x; i <= n; i += lowbit(i)) t[i] += k;
}
il ll query(int x, int y) { return getsum(y) - getsum(x - 1); }
int main() {
    scanf("%d%d", &n, &m);
    fp(i, 1, n) {
        scanf("%lld", &a[i]);
        delta[i] = a[i] - a[i - 1];
        modify(i, delta[i]);
    }
    while (m--) {
        int f, x, y;
        ll k;
        scanf("%d%d", &f, &x);
        if (f == 1) {
            scanf("%d%lld", &y, &k);
            modify(x, k);
            modify(y + 1, -k);
        } else
            printf("%lld\n", getsum(x));
    }
    return 0;
}