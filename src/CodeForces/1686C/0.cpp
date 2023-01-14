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
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
int a[N];
int ans[N];
auto solve() -> void {
  int n;
  cin >> n;
  i64 sum = 0;
  _for(i, 1, n) cin >> a[i];
  sort(a + 1, a + n + 1);
  _for(i, 1, (n + 1) / 2) ans[i * 2 - 1] = a[i];
  _for(i, 1, n - (n + 1) / 2) ans[i * 2] = a[i + (n + 1) / 2];
  ans[0] = ans[n];
  ans[n + 1] = ans[1];
  bool f = 0;
  _for(i, 1, n)
    if (!(ans[i - 1] < ans[i] && ans[i + 1] < ans[i]) &&
        !(ans[i - 1] > ans[i] && ans[i + 1] > ans[i])) {
      f = 1;
      break;
    }
  cout << (f ? "NO" : "YES") << '\n';
  if (f) return;
  _for(i, 1, n) cout << ans[i] << " \n"[i == n];
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
