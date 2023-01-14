#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 1e6 + 5;
const i64 MOD = 1e9 + 7;
i64 ffact[N];
i64 fact[N], inv_fact[N], ppow[N];
i64 qpow(i64 a, i64 b = MOD - 2, const i64 &mod = MOD) {
  i64 res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
i64 choose(i64 n, i64 m, const i64 &mod = MOD) {
  return fact[n] * inv_fact[m] % mod * inv_fact[n - m] % mod;
}
int main() {
  int n, k;
  cin >> n >> k;
  ffact[0] = fact[0] = fact[1] = inv_fact[0] = inv_fact[1] = 1;
  for (int i = 2; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
  for (int i = 1; i <= n; ++i) ffact[i] = ffact[i - 1] * fact[i] % MOD;
  i64 _ = qpow(ffact[n]);
  for (int i = n; i > 1; --i) {
    inv_fact[i] = _ * ffact[i - 1] % MOD;
    _ = _ * fact[i] % MOD;
  }
  ppow[0] = 2;
  for (int i = 1; i <= n; ++i) ppow[i] = ppow[i - 1] * ppow[i - 1] % MOD;
  i64 ans = 0;
  for (int i = k; i <= n; ++i)
    ans = (ans +
           ((i + k) % 2 ? -1 : 1) * choose(n, i) * choose(i, k) % MOD *
             (ppow[n - i] + MOD - 1) % MOD +
           MOD) %
          MOD;
  cout << ans << endl;
  return 0;
}
