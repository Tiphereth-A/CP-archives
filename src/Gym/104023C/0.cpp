#include <bits/stdc++.h>
using ll = long long;
using pii = std::pair<int, int>;
using namespace std;
constexpr bool in_same_line(pii const &u, pii const &v, pii const &w) {
  ll x1 = v.first - u.first, y1 = v.second - u.second;
  ll x2 = w.first - u.first, y2 = w.second - u.second;
  return (x1 * y2 - x2 * y1) == 0;
}
bool in_same_dir(pii const &u, pii const &v, pii const &w) {
  ll x1 = v.first - u.first, y1 = v.second - u.second;
  ll x2 = w.first - u.first, y2 = w.second - u.second;
  return in_same_line(u, v, w) && ((x1 * x2 + y1 * y2) > 0);
}
void print__(
  pii const &c, pii const &p1, pii const &p2, pii const &p3, pii const &p4) {
  cout << "YES\n";
  cout << c.first << ' ' << c.second << '\n';
  cout << p1.first << ' ' << p1.second << '\n';
  cout << p2.first << ' ' << p2.second << '\n';
  cout << p3.first << ' ' << p3.second << '\n';
  cout << p4.first << ' ' << p4.second << '\n';
}
void print(
  pii const &p0, pii const &p1, pii const &p2, pii const &p3, pii const &p4) {
  auto cond = [](pii const &x,
                 pii const &p1,
                 pii const &p2,
                 pii const &p3,
                 pii const &p4) {
    return !(in_same_dir(x, p1, p2) || in_same_dir(x, p1, p3) ||
             in_same_dir(x, p1, p4) || in_same_dir(x, p2, p3) ||
             in_same_dir(x, p2, p4) || in_same_dir(x, p3, p4));
  };
  if (cond(p0, p1, p2, p3, p4)) {
    print__(p0, p1, p2, p3, p4);
    return;
  }
  if (cond(p1, p0, p2, p3, p4)) {
    print__(p1, p0, p2, p3, p4);
    return;
  }
  if (cond(p2, p0, p1, p3, p4)) {
    print__(p2, p0, p1, p3, p4);
    return;
  }
  if (cond(p3, p0, p1, p2, p4)) {
    print__(p3, p0, p1, p2, p4);
    return;
  }
  if (cond(p4, p0, p1, p2, p3)) {
    print__(p4, p0, p1, p2, p3);
    return;
  }
}
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vector<pii> v(n);
  for (auto &i : v) cin >> i.first >> i.second;
  if (n < 5) {
    cout << "NO\n";
    return;
  }
  pii p0 = v[0], p1 = v[1], p2 = v[2], p3 = v[3], p4;
  for (int i = 4; i < n; ++i) {
    p4 = v[i];
    if (!(in_same_line(p0, p1, p2) && in_same_line(p0, p1, p3) &&
          in_same_line(p0, p1, p4))) {
      print(p0, p1, p2, p3, p4);
      return;
    }
  }
  cout << "NO\n";
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
