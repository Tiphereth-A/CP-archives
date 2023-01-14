#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MOD = 1e9 + 7, inv3 = 333333336;
i64 qpow(i64 a, i64 b) {
  i64 ans = 1;
  for (; b; a = a * a % MOD, b >>= 1)
    if (b & 1) ans = ans * a % MOD;
  return ans;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, t = 3, q;
  cin >> n >> q;
  vector<int> fact((n + 1) * t + 1), ifact((n + 1) * t + 1);
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < fact.size(); ++i) fact[i] = 1ll * fact[i - 1] * i % MOD;
  ifact.back() = qpow(fact.back(), MOD - 2);
  for (int i = ifact.size() - 2; i > 0; --i)
    ifact[i] = 1ll * ifact[i + 1] * (i + 1) % MOD;
  auto mCn = [&](int m, int n) -> i64 {
    return m < n || m < 0 || n < 0 ?
             0 :
             1ll * fact[m] * ifact[n] % MOD * ifact[m - n] % MOD;
  };
  vector<int> f((n + 1) * t + 1), a((n + 1) * t + 1);
  for (int i = 0; i <= (n + 1) * t; ++i) a[i] = mCn((n + 1) * t, i);
  for (int i = 0; i <= t; ++i) a[i] = (a[i] + (MOD - mCn(t, i))) % MOD;
  for (int i = (n + 1) * t; i >= t; --i) {
    f[i - t] = a[i];
    for (int j = 1; j < t; ++j)
      a[i - j] = ((a[i - j] - mCn(t, j) * a[i]) % MOD + MOD) % MOD;
  }
  for (int i = 1, x; i <= q; ++i) {
    cin >> x;
    cout << f[x] << '\n';
  }
  return 0;
}
