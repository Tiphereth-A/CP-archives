#include <bits/stdc++.h>
using namespace std;
struct Point {
  double l, r;
  Point(double l_ = 0, double r_ = 0): l(l_), r(r_) {}
  bool operator<(const Point &rhs) const { return r < rhs.r; }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, d, ans = 1;
  cin >> n >> d;
  vector<Point> a;
  a.reserve(n);
  for (int i = 1, x, y; i <= n; ++i) {
    cin >> x >> y;
    if (y > d) {
      cout << "-1";
      return 0;
    }
    auto dis = sqrt(d * d - y * y);
    a.emplace_back(x - dis, x + dis);
  }
  sort(a.begin(), a.end());
  double now = a.front().r;
  for (int i = 1; i < n; ++i)
    if (now < a[i].l) {
      now = a[i].r;
      ++ans;
    }
  cout << ans;
  return 0;
}
