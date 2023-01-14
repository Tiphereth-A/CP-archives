#include <cmath>
#include <cstdio>
int main() {
  int kase, cnt = 1;
  scanf("%d", &kase);
  while (kase--) {
    double t, v1, v2;
    scanf("%lf%lf%lf", &t, &v1, &v2);
    double v11 = v1 * v1, v22 = v2 * v2;
    printf("Case #%d: ", cnt++);
    if (v1 == v2) {
      puts("Yes");
      continue;
    }
    double t1 = 300.0 / v1, t2 = 900.0 / v2;
    if (t1 >= t2) {
      puts("No");
      continue;
    }
    t1 = 300 * sqrt(2.0) / v1;
    t2 = 600.0 / v2;
    if (t1 <= t2) {
      double dt = (600 * v11) * (600 * v11) -
                  4 * (v11 - v22) * (v11 * 90000 - 90000 * v22),
             x = (-600.0 * v11 + sqrt(dt)) / 2.0 / (v11 - v22);
      if ((x + 600) / v1 <= t + (600 - x) / v2) {
        puts("Yes");
        continue;
      }
    }
    double dt = (1800 * v11) * (1800 * v11) -
                4 * (v11 - v22) * (v11 * 810000 - 90000 * v22),
           x = (1800.0 * v11 - sqrt(dt)) / 2.0 / (v11 - v22);
    puts(sqrt((300.0 - x) * (300.0 - x) + 90000.0) / v1 + 900.0 / v1 <=
             t + (300 + x) / v2 ?
           "Yes" :
           "No");
  }
  return 0;
}
