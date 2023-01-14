#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r) for (int i = (l), i##end = (r); i <= i##end; ++i)
#define _rfor(i, r, l) for (int i = (r), i##end = (l); i >= i##end; --i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
const uint32_t MOD = 998244353;
i64 qpow(i64 a, i64 b = MOD - 2, const i64 &mod = MOD) {
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
auto solve() -> void {
  int n;
  cin >> n;
  vector<int> v;
  v.reserve(n);
  v.push_back(1);
  char ch;
  _for(i, 1, n) {
    cin >> ch;
    if (ch & 1) v.push_back(i);
  }
  v.push_back(n);
  i64 ans = 1;
  for (auto l = v.begin() + 1, r = v.end() - 2;; ++l, --r) {
    int len_l = *l - *(l - 1), len_r = *(r + 1) - *r;
    if (r + 1 == l) {
      (ans *= qpow(2, *l - *r)) %= MOD;
      break;
    }
    if (r + 2 == l) break;
    i64 _ = 0;
    _for(i, 0, min(len_l, len_r))
      _ += m_choose_n(len_l, i) * m_choose_n(len_r, i) % MOD;
    (ans *= _ % MOD) %= MOD;
  }
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
