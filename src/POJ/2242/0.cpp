#include <cmath>
#include <cstdio>
int main() {
  double x1, y1, x2, y2, x3, y3;
  while (~scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3))
    printf("%.2lf\n",
           acos(-1.0) * sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) *
             sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)) *
             sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3)) /
             sqrt(((sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) +
                    sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)) +
                    sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3))) /
                   2) *
                  (((sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) +
                     sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)) +
                     sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3))) /
                    2) -
                   sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))) *
                  (((sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) +
                     sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)) +
                     sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3))) /
                    2) -
                   sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3))) *
                  (((sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) +
                     sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3)) +
                     sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3))) /
                    2) -
                   sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3)))) /
             2);
}
