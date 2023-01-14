#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _rfor(i, r, l, vals...) \
  for (int i = (r), i##end = (l), ##vals; i >= i##end; --i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e3 + OFFSET;
const uint32_t MOD = 1e9 + 7;
constexpr i64 qpow(i64 a, i64 b = MOD - 2, const i64 &mod = MOD) {
  i64 res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
i64 f[N][N];
auto solve() -> void {
  i64 k, pa, pb;
  cin >> k >> pa >> pb;
  i64 A = (pa * qpow(pa + pb) % MOD), B = (1 - A + MOD) % MOD,
      C = (pa * qpow(pb) % MOD);
  _rfor(i, k, 1)
    _rfor(j, k, 0)
      f[i][j] =
        (i + j >= k ? (i + j + C) : (A * f[i + 1][j] + B * f[i][i + j])) % MOD;
  cout << f[1][0];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
