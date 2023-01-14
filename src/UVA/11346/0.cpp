#include <cmath>
#include <cstdio>
int main() {
  int n;
  double a, b, s;
  scanf("%d", &n);
  while (n--) {
    scanf("%lf%lf%lf", &a, &b, &s);
    if (s > a * b) {
      puts("0.000000%");
      continue;
    }
    if (s <= 1e-3) {
      puts("100.000000%");
      continue;
    }
    printf("%.6lf%%\n", 100.0 * (a * b - s - s * log(a * b / s)) / a / b);
  }
  return 0;
}
