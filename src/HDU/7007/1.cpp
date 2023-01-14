#include <bits/stdc++.h>
using i64 = int64_t;
#define for_(i, l, r, v...) for (i64 i = (l), i##e = (r), ##v; i <= i##e; ++i)
using namespace std;
void solve(int t_ = 0) {
  i64 n, m;
  cin >> n >> m;
  vector<i64> a(n + 1);
  for_(i, 1, n) cin >> a[i];
  vector<i64> sum(n + 1);
  for_(i, 1, n) sum[i] = sum[i - 1] + a[i];
  i64 ans = 0, now = 0;
  for_(i, 0, n * 2 - 1) {
    if (!(i % n)) ++ans;
    now = max(i64(0), now + a[i % n + 1]);
    if (now >= m) {
      cout << ans << '\n';
      return;
    }
  }
  if (sum[n] <= 0) {
    cout << "-1\n";
    return;
  }
  i64 sum_max = 0;
  for_(i, 1, n) sum_max = max(sum_max, sum[i]);
  i64 _ = m - sum_max - now;
  ans += _ / sum[n] + 1 + !!(_ % sum[n]);
  cout << ans << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
