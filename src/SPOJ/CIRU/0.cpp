#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const double eps = 1e-10, PI = acos(-1), PI2 = PI * 2;
int8_t sgn(double d) { return d < -eps ? -1 : (d > eps); }
struct Vector {
  double x, y, angle;
  Vector(double x = 0, double y = 0): x(x), y(y), angle(atan2(y, x)) {}
  double operator*(void) { return sqrt(x * x + y * y); }
  double operator^(const Vector &v) const { return x * v.y - y * v.x; }
};
struct Point {
  double x, y;
  Point(double x = 0, double y = 0): x(x), y(y) {}
  Vector operator-(const Point &p) const { return Vector(x - p.x, y - p.y); }
};
const Point origin;
struct Circle {
  Point p;
  double r;
  Circle(double _x = 0, double _y = 0, double _r = 0): p(_x, _y), r(_r) {}
  bool contains(const Circle &cir) const {
    return sgn(r - cir.r - *(cir.p - p)) != -1;
  }
  Point rotate(double d) const {
    return Point(p.x + r * cos(d), p.y + r * sin(d));
  }
  double make_size(double st, double ed) const {
    return ((rotate(st) - origin) ^ (rotate(ed) - origin)) / 2;
  }
};
void mod2pi(double &d) {
  while (d > PI2) d -= PI2;
  while (d < 0) d += PI2;
}
bool is_cross(const Circle &a, const Circle &b, double &d1, double &d2) {
  double d = *(a.p - b.p);
  if (sgn(d - a.r - b.r) != -1) return false;
  double alpha = acos((a.r * a.r + d * d - b.r * b.r) / (a.r * d * 2));
  double beta = (b.p - a.p).angle;
  mod2pi(d1 = beta + alpha);
  mod2pi(d2 = beta - alpha);
  return true;
}
double s_r(double r, double d) { return (r * r * (d - sin(d))) / 2; }
list<Circle> cir;
int main() {
  int n;
  scanf("%d", &n);
  double x, y, r;
  for (int i = 1; i <= n; ++i) {
    scanf("%lf%lf%lf", &x, &y, &r);
    cir.emplace_back(x, y, r);
  }
  double ans = 0;
  for (auto i = cir.begin(); i != cir.end();) {
    bool flag = sgn(i->r);
    for (auto j = cir.begin(); j != cir.end(); ++j)
      if (i != j && j->contains(*i)) {
        flag = false;
        break;
      }
    if (!flag) i = cir.erase(i);
    else ++i;
  }
  for (auto i = cir.begin(); i != cir.end(); ++i) {
    int c = 0;
    vector<pair<double, int>> ops;
    ops.reserve(N);
    for (auto j = cir.begin(); j != cir.end(); ++j)
      if (i != j) {
        double c1, c2;
        if (is_cross(*i, *j, c1, c2)) {
          if (c1 < c2) ++c;
          ops.emplace_back(c1, -1);
          ops.emplace_back(c2, 1);
        }
      }
    if (ops.empty()) {
      ans += i->r * i->r * PI;
      continue;
    }
    ops.emplace_back(PI2, 0);
    sort(ops.begin(), ops.end());
    double last_angle = 0;
    for (auto j = ops.begin(); j != ops.end(); ++j) {
      if (c == 0)
        ans +=
          s_r(i->r, j->first - last_angle) + i->make_size(last_angle, j->first);
      if ((c += j->second) == 0) last_angle = j->first;
    }
  }
  printf("%.3lf\n", ans);
}
