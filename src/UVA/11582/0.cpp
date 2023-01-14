#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
const uint32_t OFFSET = 5;
const uint32_t N = 1e3 + OFFSET, M = 1e4 + OFFSET, K = 21;
u64 qpow(u64 a, u64 b, u64 mod) {
  u64 res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
uint32_t f[N][M];
uint32_t loop_len[N];
void solve() {
  u64 a, b, n;
  cin >> a >> b >> n;
  cout << f[n][qpow(a % loop_len[n], b, loop_len[n])] << '\n';
}
int main() {
  for (uint32_t i = (2), iend = (N - OFFSET); i <= iend; ++i) {
    f[i][1] = 1;
    loop_len[0] = loop_len[1] = 1;
    for (uint32_t j = (2), jend = (M - OFFSET); j <= jend; ++j) {
      f[i][j] = (f[i][j - 2] + f[i][j - 1]) % i;
      if (f[i][j - 1] == 0 && f[i][j] == 1) {
        loop_len[i] = j - 1;
        break;
      }
    }
  }
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  cout.flush();
  return 0;
}
