#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const int N = 1e5 + 5;
const double EPS = 1e-6;
struct {
  int x, y;
} points[N];
auto solve() -> void {
  int a, b, n;
  double k;
  cin >> a >> b >> n >> k;
  _for(i, 1, n) cin >> points[i].x >> points[i].y;
  double _a = a, _b, _k;
  if ((k - 1) < EPS) {
    _b = tan(asin(k)) * _a;
    if ((_b - b) < EPS) {
      cout << "YES\n";
      return;
    }
    _b = b;
    _k = tan(asin(_b / sqrt(a * a + b * b) / k));
  } else {
    _b = b;
    _k = tan(asin(_b / sqrt(a * a + b * b) / k));
  }
  _b = _b - _k * _a;
  _for(i, 1, n)
    if (double __ = points[i].y - _k * points[i].x - _b; __ > EPS) {
      cout << "NO\n";
      return;
    }
  cout << "YES\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
