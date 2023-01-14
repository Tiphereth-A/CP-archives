#include <cmath>
#include <cstdio>
const double pi = acos(-1.0);
int main() {
  double a;
  while (~scanf("%lf", &a))
    printf("%.3lf %.3lf %.3lf\n",
           a * a * (1 + pi / 3 - sqrt(3.0)),
           a * a * (pi / 3 + 2 * sqrt(3.0) - 4),
           a * a * (-2 * pi / 3 + 4 - sqrt(3.0)));
  return 0;
}
