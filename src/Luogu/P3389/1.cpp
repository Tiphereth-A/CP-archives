#include <bits/stdc++.h>
#define _for(i, l, r) for (int(i) = (l); (i) <= (r); (i)++)
#define _rfor(i, l, r) for (int(i) = (l); (i) >= (r); (i)--)
#define Abs(x) (((x) > 0) ? (x) : -(x))
const double EPS = 1E-8;
int n;
double a[105][105];
void Swap(double &a, double &b) {
  double tmp = a;
  a = b;
  b = tmp;
}
int main() {
  scanf("%d", &n);
  _for(i, 1, n)
    _for(j, 1, n + 1) scanf("%lf", &a[i][j]);
  _for(i, 1, n) {
    int m = i;
    _for(j, i, n)
      if (Abs(a[j][i] - a[m][i]) <= EPS) m = j;
    if (m != i)
      _for(j, 1, n + 1) Swap(a[m][j], a[i][j]);
    if (Abs(a[i][i]) <= EPS) {
      printf("No Solution\n");
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
  _for(i, 1, n) printf("%.2lf\n", a[i][n + 1]);
  return 0;
}
