#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 5;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
struct Node {
  double x, y;
} a[N];
int n;
double f(const double &x, const double &y) {
  double ans = 0;
  _for(i, 1, n)
    ans += sqrt((x - a[i].x) * (x - a[i].x) + (y - a[i].y) * (y - a[i].y));
  return ans;
}
double thry(double l, double r, const double &x) {
  double loss, _l, _r;
  double f_l, f_r;
  _for(i, 1, 100) {
    loss = (r - l) / 3;
    _l = l + loss;
    _r = r - loss;
    f_l = f(x, _l);
    f_r = f(x, _r);
    f_l < f_r ? r = _r : l = _l;
  }
  return l + (r - l) / 2;
}
double thr(const double &l_x,
           const double &r_x,
           const double &l_y,
           const double &r_y) {
  double l = l_x, r = r_x;
  double loss, _l, _r;
  double f_l, f_r;
  double _yl, _yr;
  _for(i, 1, 100) {
    loss = (r - l) / 3;
    _l = l + loss;
    _r = r - loss;
    f_l = f(_l, _yl = thry(l_y, r_y, _l));
    f_r = f(_r, _yr = thry(l_y, r_y, _r));
    f_l < f_r ? r = _r : l = _l;
  }
  return f(l + (r - l) / 2, _yl + (_yr - _yl) / 2);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int kase;
  cin >> kase;
  cout << fixed << setprecision(0);
  while (kase--) {
    cin >> n;
    _for(i, 1, n) cin >> a[i].x >> a[i].y;
    double mx = 1e5, Mx = -1e5, my = 1e5, My = -1e5;
    _for(i, 1, n) {
      mx = min(mx, a[i].x);
      Mx = max(Mx, a[i].x);
      my = min(my, a[i].y);
      My = max(My, a[i].y);
    }
    cout << thr(mx, Mx, my, My) << "\n";
    if (kase) cout << "\n";
  }
  return 0;
}
