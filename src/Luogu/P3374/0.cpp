#include <bits/stdc++.h>
typedef long long ll;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define MAXN 5000005
ll t[MAXN], a[MAXN];
int n, m;
int lowbit(int n) { return n & (-n); }
ll getsum(int x) {
  ll ans = 0;
  for (int i = x; i; i -= lowbit(i)) ans += t[i];
  return ans;
}
void modify(int x, int k) {
  for (int i = x; i <= n; i += lowbit(i)) t[i] += k;
}
ll query(int x, int y) { return getsum(y) - getsum(x - 1); }
int main() {
  scanf("%d%d", &n, &m);
  _for(i, 1, n) {
    scanf("%lld", &a[i]);
    modify(i, a[i]);
  }
  while (m--) {
    int f, x;
    ll y;
    scanf("%d%d%lld", &f, &x, &y);
    if (f == 1) modify(x, y);
    else printf("%lld\n", query(x, y));
  }
  return 0;
}
