#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
#define(cerr << __LINE__ << ' ' << __PRETTY_FUNCTION__ << endl)
void solve([[maybe_unused]] int t_ = 0) {
  u64 n, k;
  cin >> n >> k;
  if (k > (n + 1) / 2 && n != k) cout << "NO\n";
  else {
    cout << "YES\n";
    if (n == k) cout << "1\n1\n";
    else {
      cout << "2\n";
      cout << n - k + 1 << " 1\n";
    }
  }
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
