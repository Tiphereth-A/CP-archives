#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
uint32_t cnt[32];
auto solve() -> void {
  uint32_t n;
  cin >> n;
  _for(i, 0, 31) cnt[i] = 0;
  _for(i, 1, n, x) {
    cin >> x;
    for (uint32_t j = 0; (1 << j) <= x; ++j) cnt[j] += !!(x & (1 << j));
  }
  uint32_t ans = 0;
  _for(i, 0, 31)
    if ((cnt[i] << 1) > n) ans |= (1 << i);
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
