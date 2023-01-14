#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
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
  i64 n;
  cin >> n;
  vc<int> b(n + 1);
  for_(i, 1, n) cin >> b[i];
  int q;
  cin >> q;
  const i64 sqn = ceill(sqrtl(n));
  for_(i, 1, q, op, x, y) {
    cin >> op >> x;
    if (!op) {
      cin >> y;
      if (b[x] > y) b[x] = y;
      continue;
    }
    i64 ans = numeric_limits<i64>::max();
    for_(j, max(1ll, x - sqn), min(n, x + sqn))
      ans = min(ans, (x - j) * (x - j) + b[j]);
    cout << ans << '\n';
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
