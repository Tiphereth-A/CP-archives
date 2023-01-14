#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MOD = 998244353;
i64 qpow(i64 a, i64 b) {
  i64 ans = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1) ans = ans * a % MOD;
  return ans;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int m, n, x, y;
  cin >> m >> n >> x >> y;
  vector<int> fact(n + m + 5), ifact(n + m + 5);
  fact[0] = 1;
  for (int i = 1; i < fact.size(); ++i) fact[i] = 1ll * fact[i - 1] * i % MOD;
  ifact.back() = qpow(fact.back(), MOD - 2);
  for (int i = fact.size() - 2; i >= 0; --i)
    ifact[i] = 1ll * ifact[i + 1] * (i + 1) % MOD;
  auto f = [&](int m, int n) {
    return 1ll * fact[m + n - 1] * ifact[n] % MOD * ifact[m - 1] % MOD;
  };
  i64 ans = 0;
  if (x <= n && y > n)
    for (int i = 1; i <= m; ++i)
      ans += f(i, x - 1) * f(m - i + 1, n - x) % MOD * f(m - i + 1, y - n - 1) %
             MOD * f(i, n * 2 - y) % MOD;
  else ans += f(m, n) * f(m, n - y + x) % MOD;
  cout << ans % MOD << '\n';
  return 0;
}
