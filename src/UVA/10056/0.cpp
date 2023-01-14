#include <cstdio>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, _;
    double p;
    scanf("%d%lf%d", &n, &p, &_);
    double p1 = 1, res = 0, __ = 1;
    for (int i = 1; i <= n; ++i) p1 *= (1 - p);
    int k = 0;
    while (__ > 1e-9) {
      __ = 1;
      for (int i = 0; i < k; ++i) __ *= p1;
      for (int i = 1; i < _; ++i) __ *= (1 - p);
      __ *= p;
      res += __;
      ++k;
    }
    printf("%.4lf\n", res);
  }
  return 0;
}
