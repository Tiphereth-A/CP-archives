#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
i64 H(i64 n) {
  i64 ans = 0;
  for (i64 l = 1, r = 1; l <= n; l = r + 1) {
    r = n / (n / l);
    ans += (r - l + 1) * (n / l);
  }
  return ans;
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 n;
  cin >> n;
  cout << H(n) << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
