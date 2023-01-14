#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
using pll = std::pair<ll, ll>;
using namespace std;
i64 exgcd(i64 &x, i64 &y, i64 a, i64 b) {
  if (b) {
    i64 d = exgcd(y, x, b, a % b);
    y -= a / b * x;
    return d;
  }
  x = 1;
  y = 0;
  return a;
}
void solve(int t_ = 0) {
  pll a, b;
  cin >> a.first >> a.second >> b.first >> b.second;
  i64 lx = b.first - a.first, ly = b.second - a.second;
  if (lx == 0) {
    cout << a.first - 1 << ' ' << a.second << '\n';
    return;
  }
  if (ly == 0) {
    cout << a.first << ' ' << a.second - 1 << '\n';
    return;
  }
  i64 x = 0, y = 0;
  i64 g = exgcd(y, x, lx, ly);
  cout << a.first + x << ' ' << a.second - y << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
