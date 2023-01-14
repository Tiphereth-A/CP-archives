#include <cmath>
#include <cstdio>
int main() {
  int t;
  scanf("%d", &t);
  for (int i = 1, kase = 1; i <= t; ++i) {
    double n, m, t, c;
    scanf("%lf%lf%lf%lf", &n, &m, &t, &c);
    double s[5];
    double r = c / 2, S = acos(-1.0) * r * r;
    s[0] = m * n * t * t;
    s[1] =
      (m * n) * (t - c) * (t - c) + c * m * (t - c) + c * n * (t - c) + c * c;
    s[2] = (m - 1.0) * (t - c) * n * c + (n - 1.0) * (t - c) * m * c +
           (n + m - 2.0) * c * c;
    s[4] = (n - 1.0) * (m - 1.0) * S;
    s[3] = s[0] - s[1] - s[2] - s[4];
    printf("Case %d:\n", kase++);
    for (int i = 1; i <= 4; ++i)
      printf("Probability of covering %d tile%c = %.4lf%%\n",
             i,
             (i == 1 ? ' ' : 's'),
             s[i] / s[0] * 100.0 + 1e-8);
    puts("");
  }
  return 0;
}
