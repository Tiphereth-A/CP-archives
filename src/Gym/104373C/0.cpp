#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
template <class Tp>
using vc = std::vector<Tp>;
template <typename... Ts>
void dec(Ts &...x) {
  ((--x), ...);
}
template <typename... Ts>
void inc(Ts &...x) {
  ((++x), ...);
}
using namespace std;
constexpr int sgn(i64 x) { return x < 0 ? -1 : x > 0 ? 1 : 0; }
struct Point {
  i64 x, y;
  explicit Point(i64 x = 0, i64 y = 0): x(x), y(y) {}
  static constexpr int QUAD__[9] = {5, 6, 7, 4, 0, 0, 3, 2, 1};
  int quad() const { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; }
  i64 operator^(const Point &r) const { return x * r.y - y * r.x; }
  bool operator<(const Point &r) const {
    return quad() == r.quad() ? (*this ^ r) > 0 : quad() < r.quad();
  }
};
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vc<Point> ps(n);
  for (auto &[x, y] : ps) cin >> x >> y;
  if (n < 2) {
    cout << "0\n";
    return;
  }
  sort(ps.begin(), ps.end());
  int ans = n + 1;
  auto nxt = [n](int x) { return (++x) == n ? 0 : x; };
  for (int l = 0, r = 1, cntl = 0; l < n; ++l, --cntl) {
    i64 _;
    while (r != l && (_ = ps[l] ^ ps[r]) >= 0) {
      r = nxt(r);
      ++cntl;
    }
    if (l == r) {
      ans = 0;
      break;
    }
    ans = min(ans, cntl);
  }
  cout << ans << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
