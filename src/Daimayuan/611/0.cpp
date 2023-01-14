#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const int N = 1e6 + 5;
const uint32_t MOD = 1e9 + 7;
constexpr i64 qpow(i64 a, i64 b = MOD - 2, const i64 &mod = MOD) {
  i64 res(1);
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
auto f = [](int x, int y) -> i64 {
  i64 ans = 1;
  _for(i, 2, (int)sqrt(x), cnt) {
    if (i > x) break;
    if (x % i) continue;
    cnt = 0;
    while (x % i == 0) {
      ++cnt;
      x /= i;
    }
    ans = (ans * m_choose_n(cnt + y - 1, cnt)) % MOD;
  }
  if (x != 1) ans = (ans * y) % MOD;
  return ans;
};
int main() {
  int _t;
  cin >> _t;
  while (_t--) {
    int x, y;
    cin >> x >> y;
    cout << f(x, y) * qpow(2, y - 1) % MOD << '\n';
  }
  return 0;
}
