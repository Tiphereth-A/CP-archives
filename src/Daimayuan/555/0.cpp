#include <bits/stdc++.h>
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &&i : a) cin >> i;
  int ans = 0;
  for (auto &&i : a) {
    int cntg = 0, cnte = 0;
    map<int, int> cnt;
    for (auto &&j : a) {
      if (j > i) {
        ++cntg;
        ++cnt[j - i];
      } else if (j == i) ++cnte;
    }
    if (cnte >= n / 2) {
      cout << "-1\n";
      return;
    }
    if (cntg + cnte < n / 2) continue;
    map<int, int> gcd_cnt;
    for (auto &&[k, v] : cnt) {
      for (int j = 1; j * j <= k; ++j)
        if (k % j == 0) {
          gcd_cnt[j] += v;
          if (k != j * j) gcd_cnt[k / j] += v;
        }
    }
    for (auto &&[k, v] : gcd_cnt)
      if (cnte + v >= n / 2) ans = max(ans, k);
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
