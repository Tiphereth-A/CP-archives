#include <bits/stdc++.h>
using namespace std;
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
const uint32_t N = 1e6, M = 2e5 + OFFSET, K = 21;
double harmony[N + OFFSET];
const double egamma = 0.5772156649015329;
auto __STATIC__ = []() {
  harmony[1] = 1;
  _for(i, 2, N) harmony[i] = harmony[i - 1] + 1.0 / i;
  return 0.0;
}();
auto solve() -> void {
  int n;
  cin >> n;
  double ans = 0;
  if (n > N) ans = log(n);
  else ans = harmony[n - 1] - egamma;
  cout << fixed << setprecision(6) << ans << '\n';
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
