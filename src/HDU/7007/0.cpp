#include <bits/stdc++.h>
using i64 = int64_t;
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t_ = 0;
  cin >> t_;
  while (t_--) {
    i64 n, m;
    cin >> n >> m;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<i64> sum(n + 1);
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
    i64 sum_max = 0;
    for (int i = 1; i <= n; ++i) sum_max = max(sum_max, sum[i]);
    i64 ans = 0, now = 0;
    bool f = 0;
    for (int i = 0; i < n * 2; ++i) {
      if (i % n == 0) ++ans;
      now = max(i64(0), now + a[i % n + 1]);
      if (now >= m) {
        f = 1;
        break;
      }
    }
    if (f) {
      cout << ans << '\n';
      continue;
    }
    if (sum[n] <= 0) {
      cout << "-1\n";
      continue;
    }
    i64 _ = m - sum_max - now;
    ans += _ / sum[n] + 1;
    if (_ % sum[n]) ++ans;
    cout << ans << '\n';
  }
  return 0;
}
