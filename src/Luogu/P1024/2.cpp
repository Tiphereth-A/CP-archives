#include <bits/stdc++.h>
double x[4];
using namespace std;
int main() {
  double a, b, c, d;
  scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
  double A = b * b - 3 * a * c, B = b * c - 9 * a * d, C = c * c - 3 * b * d;
  double D = B * B - 4 * A * C;
  if (A == B && A == 0) x[1] = x[2] = x[3] = (-1 * b / (3 * a));
  else if (D == 0) {
    x[1] = (-1 * b / a) + B / A;
    x[2] = x[3] = -1 * B / A / 2;
  } else if (D < 0) {
    double T = (2 * A * b - 3 * B * a) / (2 * A * sqrt(A));
    double theta = acos(T) / 3;
    x[1] = (-1 * b - 2 * sqrt(A) * cos(theta)) / (3 * a);
    x[2] = (-1 * b + sqrt(A) * (cos(theta) + sqrt(3) * sin(theta))) / (3 * a);
    x[3] = (-1 * b + sqrt(A) * (cos(theta) - sqrt(3) * sin(theta))) / (3 * a);
  }
  sort(x + 1, x + 4);
  printf("%.2lf %.2lf %.2lf", x[1], x[2], x[3]);
  return 0;
}
