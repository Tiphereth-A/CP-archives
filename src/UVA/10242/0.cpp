#include <cstdio>
#include <iostream>
using namespace std;
struct Node {
  double x, y;
  Node(double _x = 0, double _y = 0): x(_x), y(_y) {}
};
int main() {
  Node a, b, c, d;
  while (~scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y)) {
    scanf("%lf%lf%lf%lf", &c.x, &c.y, &d.x, &d.y);
    if (a.x == c.x && a.y == c.y) swap(a, b);
    if (a.x == d.x && a.y == d.y) {
      swap(a, b);
      swap(c, d);
    }
    if (b.x == d.x && b.y == d.y) swap(c, d);
    Node e(a.x + d.x - c.x, a.y + d.y - c.y);
    printf("%.3lf %.3lf\n", e.x, e.y);
  }
  return 0;
}
