#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e3 + OFFSET;
const i64 MOD = 1e9 + 7;
template <typename Tp = i64>
constexpr Tp qpow(Tp a, Tp b = MOD - 2, const Tp &mod = MOD) {
  Tp res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
i64 frac[N * 2], ffrac[N], inv[N];
auto __ = []() {
  ffrac[0] = frac[0] = inv[0] = frac[1] = inv[1] = 1;
  _for(i, 2, 2 * N - 1) frac[i] = frac[i - 1] * i % MOD;
  _for(i, 1, N - 1) ffrac[i] = ffrac[i - 1] * frac[i] % MOD;
  i64 _ = qpow(ffrac[N - 1]);
  _rfor(i, N - 1, 2) {
    inv[i] = _ * ffrac[i - 1] % MOD;
    _ = _ * frac[i] % MOD;
  }
  return 0;
}();
auto m_choose_n(int m, int n) -> i64 {
  return m < n ? 0 : frac[m] * inv[n] % MOD * inv[m - n] % MOD;
}
pii obstruct[M];
i64 f[N];
void solve() {
  int h, w, m;
  cin >> h >> w >> m;
  _for(i, 1, m) cin >> obstruct[i].first >> obstruct[i].second;
  obstruct[m + 1] = {h, w};
  sort(obstruct + 1, obstruct + m + 1);
  _for(i, 1, m + 1) {
    auto &obsi = obstruct[i];
    f[i] = m_choose_n(obsi.first + obsi.second - 2, obsi.first - 1);
    if (!f[i]) continue;
    _for(j, 1, i - 1) {
      auto &obsj = obstruct[j];
      if (obsj.first > obsi.first || obsj.second > obsi.second) continue;
      (((f[i] -= f[j] *
                 m_choose_n(obsi.first - obsj.first + obsi.second - obsj.second,
                            obsi.first - obsj.first) %
                 MOD) %= MOD) += MOD) %= MOD;
    }
  }
  cout << f[m + 1];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
