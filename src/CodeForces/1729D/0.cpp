#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define foreach_ref_(i, container) for (auto &i : container)
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vector<int> a(n);
  foreach_ref_(i, a) cin >> i;
  for_(i, 0, n - 1, x) {
    cin >> x;
    a[i] = x - a[i];
  }
  sort(a.begin(), a.end());
  int l = 0, r = n - 1;
  int ans = 0;
  while (l < r) {
    if (a[r] + a[l++] >= 0) {
      ++ans;
      --r;
    }
  }
  cout << ans << '\n';
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
