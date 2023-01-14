#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
#define MAXN 5000005
ll t[MAXN], a[MAXN], delta[MAXN];
int n, m;
int lowbit(int n) { return n & (-n); }
ll getsum(int x) {
  ll ans = 0;
  for (int i = x; i > 0; i -= lowbit(i)) ans += t[i];
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
    } else printf("%lld\n", getsum(x));
  }
  return 0;
}
