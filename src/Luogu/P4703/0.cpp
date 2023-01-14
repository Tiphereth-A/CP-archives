#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _run_return(expressions, val) return (expressions), val
#define _run_exit(expressions) _run_return(expressions, 0)
pair<double, double> a[11];
int n;
double l, _l;
bool check(double x, double y) {
  _for(i, 1, n)
    if (sqrt((a[i].first - x) * (a[i].first - x) +
             (a[i].second - y) * (a[i].second - y)) < _l)
      return false;
  return true;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n >> l;
  _l = l / n + 1e-6;
  cout << fixed << setprecision(6);
  double x, y;
  _for(i, 1, n) {
    cin >> x >> y;
    a[i] = {x, y};
  }
  if (n == 1) {
    if (check(0, 0)) _run_exit(cout << 0 << ' ' << 0);
    if (check(0, l)) _run_exit(cout << 0 << ' ' << l);
    if (check(l, 0)) _run_exit(cout << l << ' ' << 0);
    if (check(l, l)) _run_exit(cout << l << ' ' << l);
    _run_exit(cout << "GG\n");
  }
  default_random_engine g(time(nullptr));
  uniform_real_distribution<double> u_point(0, l);
  while (1)
    if (check(x = u_point(g), y = u_point(g))) _run_exit(cout << x << ' ' << y);
  return 0;
}
