#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1e7 + OFFSET;
const uint32_t MOD = 1e9 + 7;
template <typename Tp = i64>
constexpr Tp qpow(Tp a, Tp b = MOD - 2, const Tp &mod = MOD) {
  Tp res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
int fact[N * 2], inv[N];
auto __STATIC__ = []() {
  fact[0] = inv[0] = inv[1] = 1;
  _for(i, 1, N * 2 - 1) fact[i] = (1ll * i * fact[i - 1]) % MOD;
  _for(i, 2, N - 1) inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
  _for(i, 2, N - 1) inv[i] = (1ll * inv[i] * inv[i - 1]) % MOD;
  return 0.0;
}();
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  cout << 1ll * fact[n + m - 1] * inv[m] % MOD * inv[n - 1] % MOD;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
