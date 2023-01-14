#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _double_equ(x, y) (abs((x) - (y)) <= EPS)
const double EPS = 1e-8;
int n;
double a[55][55];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n;
  _for(i, 1, n)
    _for(j, 1, n + 1) cin >> a[i][j];
  int now = 1;
  _for(i, 1, n, m) {
    m = now;
    _for(j, now + 1, n)
      if (abs(a[j][i]) > abs(a[m][i])) m = j;
    if (_double_equ(a[m][i], 0)) continue;
    if (m != now)
      _for(j, 1, n + 1) swap(a[m][j], a[now][j]);
    _for(j, 1, n) {
      if (j == now) continue;
      double tmp = a[j][i] / a[now][i];
      a[j][i] = 0;
      _for(k, i + 1, n + 1) a[j][k] -= a[now][k] * tmp;
    }
    ++now;
  }
  if (now != n + 1) {
    _for(i, now, n)
      if (!_double_equ(a[i][n + 1], 0)) {
        cout << "-1";
        return 0;
      }
    cout << "0";
    return 0;
  }
  _for(i, 1, n)
    if (_double_equ(a[i][n + 1] /= a[i][i], 0)) a[i][n + 1] = 0;
  cout << fixed << setprecision(2);
  _for(i, 1, n) cout << 'x' << i << '=' << a[i][n + 1] << '\n';
  return 0;
}
