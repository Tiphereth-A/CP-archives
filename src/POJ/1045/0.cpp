#include <cmath>
#include <cstdio>
double w[1000];
int main() {
  double v, r, c;
  int n;
  scanf("%lf%lf%lf%d", &v, &r, &c, &n);
  int i = 0;
  for (i = 0; i < n; ++i) {
    scanf("%lf", w + i);
    w[i] = (v * c * r * w[i]) / sqrt(1 + c * c * r * r * w[i] * w[i]);
  }
  for (i = 0; i < n; ++i) printf("%.3lf\n", w[i]);
  return 0;
}
