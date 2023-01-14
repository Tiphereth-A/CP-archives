#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
struct Node {
  long double x, y, w;
} a[N];
int n;
long double f(const long double &x, const long double &y) {
  long double ans = 0;
  _for(i, 1, n)
    ans +=
      a[i].w * sqrt((x - a[i].x) * (x - a[i].x) + (y - a[i].y) * (y - a[i].y));
  return ans;
}
long double thry(long double l, long double r, const long double &x) {
  long double loss, _l, _r;
  long double f_l, f_r;
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
tuple<long double, long double> thr(const long double &l_x,
                                    const long double &r_x,
                                    const long double &l_y,
                                    const long double &r_y) {
  long double l = l_x, r = r_x;
  long double loss, _l, _r;
  long double f_l, f_r;
  long double _yl, _yr;
  _for(i, 1, 100) {
    loss = (r - l) / 3;
    _l = l + loss;
    _r = r - loss;
    f_l = f(_l, _yl = thry(l_y, r_y, _l));
    f_r = f(_r, _yr = thry(l_y, r_y, _r));
    f_l < f_r ? r = _r : l = _l;
  }
  return make_tuple(l + (r - l) / 2, _yl + (_yr - _yl) / 2);
}
int main() {
  cin >> n;
  _for(i, 1, n) cin >> a[i].x >> a[i].y >> a[i].w;
  long double mx = 1e5, Mx = -1e5, my = 1e5, My = -1e5;
  _for(i, 1, n) {
    mx = min(mx, a[i].x);
    Mx = max(Mx, a[i].x);
    my = min(my, a[i].y);
    My = max(My, a[i].y);
  }
  long double x, y;
  tie(x, y) = thr(mx, Mx, my, My);
  cout << fixed << setprecision(3) << x << " " << y;
  return 0;
}
