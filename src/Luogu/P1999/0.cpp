#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define MOD(x, p) ((x) % (p))
typedef long long ll;
#define P 1000000007
ll qpow(ll a, ll b) {
  ll ans = 1, c = MOD(a, P);
  while (b) {
    if (b & 1) ans = MOD(ans * c, P);
    c = MOD(c * c, P);
    b >>= 1;
  }
  return MOD(ans, P);
}
ll inv(ll x, ll y) {
  if (y > x) return 0;
  ll ans = 1;
  _for(i, 1, y) {
    ll tmp1 = MOD(x - y + i, P), tmp2 = MOD(i, P);
    ans = MOD(ans * MOD(tmp1 * qpow(tmp2, P - 2), P), P);
  }
  return MOD(ans, P);
}
ll lucas(ll x, ll y) {
  if (y == 0) return 1;
  return MOD(inv(x % P, y % P) * lucas(x / P, y / P), P);
}
int main() {
  ll m, n;
  scanf("%lld%lld", &m, &n);
  if (m < n) {
    printf("0\n");
    return 0;
  }
  printf("%lld\n", MOD(lucas(m, n) * qpow(2, m - n), P));
  return 0;
}
