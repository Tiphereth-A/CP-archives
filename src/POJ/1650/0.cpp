#include <cstdio>
int main() {
  double n;
  int d;
  scanf("%lf%d", &n, &d);
  double min_diff = 100;
  int a = 1, b = 1, min_a = 1, min_b = 1;
  while (a <= d && b <= d) {
    double now = 1.0l * a / b;
    if (now > n) {
      if (now - n < min_diff) {
        min_diff = now - n;
        min_a = a;
        min_b = b;
      }
      ++b;
    } else if (now < n) {
      if (n - now < min_diff) {
        min_diff = n - now;
        min_a = a;
        min_b = b;
      }
      ++a;
    } else {
      min_diff = 0;
      min_a = a;
      min_b = b;
      break;
    }
  }
  printf("%d %d", min_a, min_b);
}
