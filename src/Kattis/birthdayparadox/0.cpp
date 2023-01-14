#include <bits/stdc++.h>
using namespace std;
const int N = 405;
int c[N], f[N];
int main() {
#define _(a)    \
  if (a[i] > 1) \
    for (int j = 2; j <= a[i]; ++j) ans -= log10(j);
  int n;
  cin >> n;
  int k = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> c[i];
    ++f[c[i]];
    k += c[i];
  }
  double ans = -k * log10(365);
  for (int i = 0; i < n; ++i) ans += log10(365 - i);
  for (int i = 2; i <= k; ++i) ans += log10(i);
  for (int i = 1; i < N; ++i) {
    _(c);
    _(f);
  }
  printf("%.12lf", ans);
  return 0;
}
