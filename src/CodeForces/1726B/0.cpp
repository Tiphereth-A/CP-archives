#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 n, m;
  cin >> n >> m;
  if (n > m) {
    cout << "No\n";
    return;
  }
  if (n == m) {
    cout << "Yes\n";
    for_(i, 1, n) cout << '1' << " \n"[i == n];
    return;
  }
  if (n & 1) {
    cout << "Yes\n";
    for_(i, 1, n - 1) cout << "1 ";
    cout << m - n + 1 << '\n';
    return;
  }
  if (~m & 1) {
    cout << "Yes\n";
    for_(i, 1, n - 2) cout << "1 ";
    cout << (m - n + 2) / 2 << ' ' << (m - n + 2) / 2 << '\n';
    return;
  }
  cout << "No\n";
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
