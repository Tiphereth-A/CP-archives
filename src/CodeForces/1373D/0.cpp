#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
int a[N];
auto solve() -> void {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  i64 sum = 0, ans1 = 0;
  for (int i = 1; i < n; i += 2) {
    if ((sum += a[i] - a[i - 1]) < 0) sum = 0;
    chkmax(ans1, sum);
  }
  sum = 0;
  for (int i = 2; i < n; i += 2) {
    if ((sum += a[i - 1] - a[i]) < 0) sum = 0;
    chkmax(ans1, sum);
  }
  i64 ans = 0;
  for (int i = 0; i < n; i += 2) ans += a[i];
  cout << ans + ans1 << '\n';
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
