#include <algorithm>
#include <cstdio>
struct Node {
  double j, f, p;
  bool operator<(const Node &oth) const { return p > oth.p; }
} a[1005];
int main() {
  int m, n;
  while (scanf("%d%d", &m, &n) && (~m && ~n)) {
    double sum = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%lf%lf", &a[i].j, &a[i].f);
      a[i].p = a[i].j / a[i].f;
    }
    std::sort(a + 1, a + n + 1);
    for (int j = 1; j <= n; ++j) {
      if (m - a[j].f > 1e-3) {
        sum += a[j].j;
        m -= a[j].f;
      } else {
        sum += m * a[j].p;
        break;
      }
    }
    printf("%.3lf\n", sum);
  }
}
