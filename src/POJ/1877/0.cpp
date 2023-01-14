#include <algorithm>
#include <cstdio>
int a[1005], kase;
int main() {
  int r, c;
  while (scanf("%d%d", &r, &c), (r || c)) {
    int n = r * c;
    for (int i = 0; i < n; ++i) {
      scanf("%d", a + i);
      a[i] *= 100;
    }
    std::sort(a, a + n);
    double v, h = a[0];
    scanf("%lf", &v);
    int cnt = 1;
    for (int i = 1; i < n; ++i)
      if ((a[i] - a[i - 1]) * i < v) {
        v -= i * (a[i] - a[i - 1]);
        ++cnt;
        h = a[i];
      } else {
        h += v / i;
        v = 0;
        break;
      }
    if (v) h += v / n;
    printf(
      "Region %d\nWater level is %.2lf meters.\n%.2lf percent of the region is "
      "under water.\n\n",
      ++kase,
      h / 100,
      cnt * 100.0 / n);
  }
}
