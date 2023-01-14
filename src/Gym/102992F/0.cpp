#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ldb = long double;
i64 n, m;
ldb p;
ldb f(ldb k) { return (n * k + m) / (1 - pow(1 - p, k)); }
void solve() {
  i64 _p;
  scanf("%lld%lld%lld", &n, &m, &_p);
  p = _p * 1e-4;
  ldb ans = DBL_MAX;
  ldb l = 1, r = 1e15;
  while ((r - l) > 5e2) {
    ldb lm = (l * 2 + r) / 3, rm = (l + 2 * r) / 3;
    ldb lf = f(floor(lm)), rf = f(floor(rm));
    if (lf > rf) l = lm;
    else r = rm;
  }
  for (ldb i = l - 1; i <= r + 1; i += 1) ans = min(ans, f(floor(i)));
  printf("%.10Lf\n", ans);
}
int main() {
  int _t;
  scanf("%d", &_t);
  while (_t--) solve();
  return 0;
}
