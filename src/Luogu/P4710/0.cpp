#include <bits/stdc++.h>
int main() {
  long double v, theta;
  scanf("%Lf%Lf", &v, &theta);
  long double vx = v * sin(theta), vy = v * cos(theta), g = 10;
  printf("%.3Lf %.3Lf", vx * vy / g, vy * vy / g / 2.0);
  return 0;
}
