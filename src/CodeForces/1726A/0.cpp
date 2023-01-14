#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vector<int> a(n);
  for_(i, 0, n - 1) cin >> a[i];
  if (n == 1) {
    cout << "0\n";
    return;
  }
  int ans = max(0, a[n - 1] - a[0]);
  int m = INT_MAX, M = 0;
  for_(i, 1, n - 1) M = max(M, a[i]);
  for_(i, 0, n - 2) m = min(m, a[i]);
  for_(i, 0, n - 2) ans = max(ans, a[i] - a[i + 1]);
  cout << max({ans, a[n - 1] - m, M - a[0]}) << '\n';
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
