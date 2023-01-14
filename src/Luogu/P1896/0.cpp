#include <bits/stdc++.h>
using namespace std;
using u128 = __uint128_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 1;
const uint32_t N = 9 + OFFSET, K = (1 << 9) + OFFSET;
auto popcount = [](unsigned x) -> int { return __builtin_popcount(x); };
u128 f[N][K][N * N];
int popc[K];
ostream &operator<<(ostream &os, u128 n) {
  if (n > 9) os << (u128)(n / 10);
  os << (uint_fast16_t)(n % 10);
  return os;
}
auto solve() -> void {
  int n, k;
  cin >> n >> k;
  static int STATE = (1 << n) - 1;
  _for(s, 0, STATE) {
    if ((popc[s] = popcount(s)) > k) continue;
    if ((s << 1 & s) || (s >> 1 & s)) continue;
    f[1][s][popc[s]] = 1;
  }
  _for(i, 2, n)
    _for(s_now, 0, STATE) {
      if ((s_now << 1 & s_now) || (s_now >> 1 & s_now)) continue;
      _for(s_pre, 0, STATE) {
        if ((s_pre << 1 & s_pre) || (s_pre >> 1 & s_pre)) continue;
        if ((s_now & s_pre) || (s_now << 1 & s_pre) || (s_now >> 1 & s_pre))
          continue;
        _for(c, 0, k - popc[s_now])
          f[i][s_now][popc[s_now] + c] += f[i - 1][s_pre][c];
      }
    }
  u128 ans = 0;
  _for(s_now, 0, STATE) ans += f[n][s_now][k];
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
