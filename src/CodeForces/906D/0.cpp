#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
unordered_map<int, int> phi;
int calc_phi(int p) {
  int ans = p;
  for (int i = 2; i <= sqrt(p); ++i)
    if (p % i == 0) {
      ans = ans / i * (i - 1);
      while (p % i == 0) p /= i;
    }
  if (p > 1) ans = ans / p * (p - 1);
  return ans;
}
i64 qpow(i64 a, i64 b, i64 mod) {
  i64 res = 1;
  a > mod ? (a %= mod) += mod : 0;
  for (; b; b >>= 1, (a *= a) > mod ? (a %= mod) += mod : 0)
    if (b & 1) (res *= a) > mod ? (res %= mod) += mod : 0;
  return res;
}
int w[N];
i64 dfs(int l, int r, int x, i64 p) {
  if (x > r || p == 1) return 1;
  return qpow(w[x], dfs(l, r, x + 1, phi[p]), p);
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", w + i);
  int _m = m;
  phi[1] = 1;
  while (_m > 1) {
    phi[_m] = calc_phi(_m);
    _m = phi[_m];
  }
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%lld\n", dfs(l, r, l, m) % m);
  __end_kase:;
  }
  return 0;
}
