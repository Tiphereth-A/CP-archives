#include <bits/stdc++.h>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define Rep for_
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
void solve(int t_ = 0) {
  double S, ans;
  int n, a;
  cin >> n;
  Rep(i, 1, n) cin >> a, S += a;
  ans = S / (1.0 + n);
  cout << fixed << setprecision(8) << ans * 2;
  Rep(i, 2, n) cout << ' ' << fixed << setprecision(8) << ans;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
