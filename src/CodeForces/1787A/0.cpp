#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 n;
  cin >> n;
  if (n & 1) {
    cout << "-1\n";
    return;
  }
  cout << "1 " << n / 2 << '\n';
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
