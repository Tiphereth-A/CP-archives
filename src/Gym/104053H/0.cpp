#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const string AB_[2] = {"Bob", "Alice"};
void solve() {
  i64 n, k;
  cin >> n >> k;
  vector<bool> vis(1000000 + 1);
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    vis[x] = 1;
  }
  int even = 0, odd = 1;
  int cnt_even = 0, cnt_odd = 0;
  for (int i = 0; i <= 1000000; ++i) {
    if (cnt_odd > k && cnt_even > k) break;
    if (vis[i]) continue;
    if (i & 1) {
      if (cnt_odd > k) continue;
      ++cnt_odd;
      odd = i;
    } else {
      if (cnt_even > k) continue;
      ++cnt_even;
      even = i;
    }
  }
  cout << AB_[even < odd] << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve();
  return 0;
}
