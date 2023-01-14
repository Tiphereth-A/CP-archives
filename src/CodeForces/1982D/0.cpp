#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
template <class Tp>
using vec = vector<Tp>;
template <class Tp>
using vvec = vector<vector<Tp>>;
#define fors_(i, l, r, s, ...) \
  for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
void solve([[maybe_unused]] int t_ = 0) {
  int n, m, k;
  cin >> n >> m >> k;
  vvec<i64> mp(n, vec<i64>(m)), a(n, vec<i64>(m));
  for (auto &i : mp)
    for (auto &j : i) cin >> j;
  char ch;
  i64 sum = 0;
  for_(i, 0, n - 1)
    for_(j, 0, m - 1) {
      cin >> ch;
      a[i][j] = ch & 1 ? 1 : -1;
      sum += ch & 1 ? mp[i][j] : -mp[i][j];
    }
  if (sum == 0) {
    cout << "YES\n";
    return;
  }
  for_(i, 0, n - 1)
    for_(j, 0, m - 1)
      a[i][j] += (j ? a[i][j - 1] : 0) + (i ? a[i - 1][j] : 0) -
                 (i && j ? a[i - 1][j - 1] : 0);
  i64 g = 0;
  for_(i, k - 1, n - 1)
    for_(j, k - 1, m - 1) {
      i64 now = a[i][j] - (i < k ? 0 : a[i - k][j]) -
                (j < k ? 0 : a[i][j - k]) +
                (i < k || j < k ? 0 : a[i - k][j - k]);
      if (!now) continue;
      g = g ? gcd(g, now) : now;
    }
  cout << (g == 0 || sum % g ? "NO\n" : "YES\n");
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
