#include <bits/stdc++.h>
using namespace std;
void solve([[maybe_unused]] int t_ = 0) {
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  cout << (((x1 > y1 && x2 > y2) || (x1 < y1 && x2 < y2)) ? "YES\n" : "NO\n");
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
