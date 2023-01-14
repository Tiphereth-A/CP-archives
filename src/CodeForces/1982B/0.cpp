#include <bits/stdc++.h>
using namespace std;
void solve([[maybe_unused]] int t_ = 0) {
  int x, k, y;
  cin >> x >> y >> k;
  if (x % y == 0) ++x, --k;
  while (x != 1) {
    int r = (y - x % y) % y;
    if (k < r) {
      cout << x + k << '\n';
      return;
    }
    k -= r;
    x += r;
    while (x && x % y == 0) x /= y;
  }
  cout << k % (y - 1) + 1 << '\n';
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cerr << fixed << setprecision(6);
  int i_ = 0;
  int t_ = 0;
  cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
