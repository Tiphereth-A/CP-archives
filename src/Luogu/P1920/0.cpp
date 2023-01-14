#include <bits/stdc++.h>
int n;
double x, lim, s = 1.0, ans = 0.0;
int main() {
  scanf("%lf%d", &x, &n);
  lim = -log(1.0 - x);
  for (int i = 1; i <= n; ++i) {
    s *= x;
    ans += s / i;
    if (round(ans * 10000.0) >= round(lim * 10000.0)) break;
  }
  printf("%.4lf\n", ans);
}
