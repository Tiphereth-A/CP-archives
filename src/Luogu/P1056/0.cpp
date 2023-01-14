#include <bits/stdc++.h>
using namespace std;
int main() {
  int m, n, k, l, d;
  cin >> m >> n >> k >> l >> d;
  int x[1010] = {0}, y[1010] = {0};
  for (int i = 1; i <= d; i++) {
    int xi, yi, pi, qi;
    cin >> xi >> yi >> pi >> qi;
    if (xi == pi) x[min(yi, qi)]++;
    else y[min(xi, pi)]++;
  }
  int xb[1005] = {0}, yb[1005] = {0};
  for (int i = 1; i <= k; i++) {
    int MAXN = -1;
    int p;
    for (int j = 1; j <= m; j++)
      if (y[j] > MAXN) {
        MAXN = y[j];
        p = j;
      }
    xb[p]++;
    y[p] = 0;
  }
  for (int i = 1; i <= l; i++) {
    int MAXN = -1;
    int p;
    for (int j = 1; j <= m; j++)
      if (x[j] > MAXN) {
        MAXN = x[j];
        p = j;
      }
    yb[p]++;
    x[p] = 0;
  }
  for (int i = 1; i <= m; i++)
    if (xb[i] > 0)
      for (int j = 1; j <= xb[i]; j++) cout << i << ' ';
  cout << endl;
  for (int i = 1; i <= n; i++)
    if (yb[i] > 0)
      for (int j = 1; j <= yb[i]; j++) cout << i << ' ';
  cout << endl;
  return 0;
}
