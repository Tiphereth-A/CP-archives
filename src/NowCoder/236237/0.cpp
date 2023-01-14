#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const int N = 1e5 + 5;
int a[N];
int mina[N];
auto solve() -> void {
  uint32_t n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  mina[0] = INT32_MAX;
  _for(i, 1, n) mina[i] = min(a[i], mina[i - 1]);
  int ans = -1;
  _for(i, 1, n) ans = max(ans, a[i] - mina[i - 1]);
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
