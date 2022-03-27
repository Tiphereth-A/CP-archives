#include <cstdio>
#define il inline
typedef long long ll;
#define fp(i, l, r) for (register int i = (l); i <= (r); ++i)
#define MAXN 5000005
ll t[MAXN], a;
int n, m;
il int lowbit(int n) { return n & (-n); }
il ll getsum(int x) {
    ll ans = 0;
    for (int i = x; i; i -= lowbit(i)) ans += t[i];
    return ans;
}
il void modify(int x, int k) {
    for (int i = x; i <= n; i += lowbit(i)) t[i] += k;
}
il ll query(int x, int y) { return getsum(y) - getsum(x - 1); }
int main() {
    scanf("%d%d", &n, &m);
    fp(i, 1, n) {
        scanf("%lld", &a);
        modify(i, a);
    }
    while (m--) {
        int f, x;
        ll y;
        scanf("%d%d%lld", &f, &x, &y);
        if (f == 1)
            modify(x, y);
        else
            printf("%lld\n", query(x, y));
    }
    return 0;
}