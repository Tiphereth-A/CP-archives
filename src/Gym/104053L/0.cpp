#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const i64 MOD = 998244353;
constexpr i64 qpow(i64 a, i64 b, i64 mod) {
  i64 ret = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) ret = ret * a % mod;
  return ret;
}
const int N = 2e5 + 5;
i64 fact[N];
i64 comb(i64 n, i64 m) {
  if (n < m) return 0;
  return fact[n] * qpow(fact[n - m], MOD - 2, MOD) % MOD *
         qpow(fact[m], MOD - 2, MOD) % MOD;
}
void solve() {
  i64 n, m;
  cin >> n >> m;
  cout << fact[n] * comb(n - 1, m - 1) % MOD << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int i_ = 0;
  fact[0] = 1;
  for (int i = 1; i < N; ++i) fact[i] = fact[i - 1] * i % MOD;
  int t_ = 0;
  cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve();
  return 0;
}
