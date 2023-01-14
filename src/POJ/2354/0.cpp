#include <cmath>
#include <cstdio>
double dist(double l1, double d1, double l2, double d2) {
  l1 *= acos(-1.0) / 180;
  d1 *= acos(-1.0) / 180;
  l2 *= acos(-1.0) / 180;
  d2 *= acos(-1.0) / 180;
  return 3437.5 * acos(cos(l1) * cos(l2) * cos(d1 - d2) + sin(l1) * sin(l2));
}
char str[100];
int main() {
  for (int i = 0; i < 9; ++i) scanf("%*s");
  double d, m, s;
  scanf("%lf^%lf'%lf\" %s", &d, &m, &s, str);
  double l1, l2, d1, d2, dis;
  l1 = d + m / 60 + s / 3600;
  if (str[0] == 'S') l1 *= -1;
  scanf("%s", str);
  scanf("%lf^%lf'%lf\" %s.", &d, &m, &s, str);
  d1 = d + m / 60 + s / 3600;
  if (str[0] == 'W') d1 *= -1;
  for (int i = 0; i < 5; ++i) scanf("%s", str);
  scanf("%lf^%lf'%lf\" %s", &d, &m, &s, str);
  l2 = d + m / 60 + s / 3600;
  if (str[0] == 'S') l2 *= -1;
  scanf("%s", str);
  scanf("%lf^%lf'%lf\" %s.", &d, &m, &s, str);
  d2 = d + m / 60 + s / 3600;
  if (str[0] == 'W') d2 *= -1;
  scanf("%s", str);
  dis = dist(l1, d1, l2, d2);
  printf("The distance to the iceberg: %.2lf miles.\n", dis);
  if (floor(dis + 0.005) < 100) printf("DANGER!\n");
  return 0;
}
