#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (int(i) = (l); (i) <= (r); (i)++)
#define _rfor(i, l, r) for (int(i) = (l); (i) >= (r); (i)--)
const double EPS = 1E-8;
int n;
double a[105][105];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n;
  _for(i, 1, n)
    _for(j, 1, n + 1) cin >> a[i][j];
  _for(i, 1, n) {
    int m = i;
    _for(j, i, n)
      if (abs(a[j][i] - a[m][i]) <= EPS) m = j;
    if (m != i)
      _for(j, 1, n + 1) swap(a[m][j], a[i][j]);
    if (abs(a[i][i]) <= EPS) {
      cout << "No Solution\n";
      return 0;
    }
    _for(j, i + 1, n) {
      double tmp = a[j][i] / a[i][i];
      _for(k, i, n + 1) a[j][k] -= a[i][k] * tmp;
    }
  }
  _rfor(i, n, 1) {
    _for(j, i + 1, n) a[i][n + 1] -= a[i][j] * a[j][n + 1];
    a[i][n + 1] /= a[i][i];
  }
  cout << fixed << setprecision(2);
  _for(i, 1, n) cout << a[i][n + 1] << '\n';
  return 0;
}
