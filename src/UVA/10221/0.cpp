#include <cmath>
#include <cstdio>
#include <cstring>
double s, a;
char c[5];
int main() {
  while (~scanf("%lf %lf %s", &s, &a, c)) {
    if (c[0] == 'm') a /= 60;
    if (a > 180) a = 360 - a;
    double ang = a * acos(-1.0) / 180.0,
           arc = 2.0 * (s + 6440.0) * sin(ang / 2.0), cho = ang * (s + 6440.0);
    printf("%.6lf %.6lf\n", cho, arc);
  }
  return 0;
}
