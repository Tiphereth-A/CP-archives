#include <cstdio>
struct Point {
  double x, y;
} P[1005];
int main() {
  int _;
  while (~scanf("%d", &_)) {
    for (int i = 1; i <= _; ++i) scanf("%lf%lf", &P[i].x, &P[i].y);
    P[_ + 1] = P[1];
    printf("%d ", _);
    for (int i = 1; i <= _; ++i)
      printf("%.6lf %.6lf%c",
             (P[i].x + P[i + 1].x) / 2,
             (P[i].y + P[i + 1].y) / 2,
             " \n"[i == _]);
  }
}
