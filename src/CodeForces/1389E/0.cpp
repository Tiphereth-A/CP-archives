#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
auto solve() -> void {
  i64 m, d, w;
  cin >> m >> d >> w;
  w /= gcd(w, d - 1);
  i64 _ = min(m, d), __ = _ / w;
  cout << (_ * 2 - w * __ - w) * __ / 2 << '\n';
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
