#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
i64 f[90];
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 x;
  cin >> x;
  i64 p = lower_bound(f, f + 90, x) - f, q = p - 1;
  i64 ans = 0;
  while (x) {
    x = min(f[p] - x, x - f[q]);
    q = (p = lower_bound(f, f + 90, x) - f) - 1;
    ++ans;
  }
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  f[1] = f[2] = 1;
  for (int i = 3; i < 90; i++) f[i] = f[i - 1] + f[i - 2];
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
