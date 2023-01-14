#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
template <class Tp>
using vec = vector<Tp>;
#define fors_(i, l, r, s, ...) \
  for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
void solve([[maybe_unused]] int t_ = 0) {
  int n, l, r;
  cin >> n >> l >> r;
  vec<int> a(n);
  for_(i, 0, n - 1) cin >> a[i];
  int ans = 0;
  i64 sum = 0;
  for_(r2, 0, n - 1, l2 = 0) {
    sum += a[r2];
    while (l2 < r2 && sum > r) sum -= a[l2++];
    if (l <= sum && sum <= r) {
      ++ans;
      l2 = r2 + 1;
      sum = 0;
    }
  }
  cout << ans << '\n';
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cerr << fixed << setprecision(6);
  int i_ = 0;
  int t_ = 0;
  cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
