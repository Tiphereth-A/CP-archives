#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 10007, M = 1e6 + OFFSET;
const uint32_t MOD = 10007;
template <typename Tp = i64>
constexpr Tp qpow(Tp a, Tp b = MOD - 2, const Tp &mod = MOD) {
  Tp res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
i64 fact[N * 2], inv_fact[N];
auto __STATIC__ = []() {
  static i64 ffact[N];
  ffact[0] = fact[0] = inv_fact[0] = fact[1] = inv_fact[1] = 1;
  _for(i, 2, N * 2 - 1) fact[i] = fact[i - 1] * i % MOD;
  _for(i, 1, N - 1) ffact[i] = ffact[i - 1] * fact[i] % MOD;
  i64 _ = qpow(ffact[N - 1]);
  _rfor(i, N - 1, 2) {
    inv_fact[i] = _ * ffact[i - 1] % MOD;
    _ = _ * fact[i] % MOD;
  }
  return 0.0;
}();
auto m_choose_n = [](int m, int n, i64 mod = MOD) -> i64 {
  return m < n ? 0 : fact[m] * inv_fact[n] % mod * inv_fact[m - n] % mod;
};
int a[M];
auto solve() -> void {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i += 2) a[(i + 1) / 2] = i;
  for (int i = 2; i <= n; i += 2) a[n - (i - 1) / 2] = i;
  int ans = 0;
  _for(i, 1, n)
    (ans += m_choose_n((n - 1) / MOD, (i - 1) / MOD) *
            m_choose_n((n - 1) % MOD, (i - 1) % MOD) % MOD * a[i] % MOD) %= MOD;
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
