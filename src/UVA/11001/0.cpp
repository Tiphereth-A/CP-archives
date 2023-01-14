#include <cstdio>
int main() {
  double a, b;
  while (~scanf("%lf%lf", &a, &b) && a + b)
    printf("%d\n",
           (a <= b || 0.5 * a / b - (int)(0.5 * a / b) == 0.5) ? 0 :
           a <= 2 * b                                          ? 1 :
           0.5 * a / b - (int)(0.5 * a / b) < 0.5 ? (int)(0.5 * a / b) :
                                                    (int)(0.5 * a / b) + 1);
  return 0;
}
