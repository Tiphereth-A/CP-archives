#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
namespace _Point_2D {
const double EPS = 1e-12;
struct Point_2D {
  double x, y;
  Point_2D(double x = 0, double y = 0): x(x), y(y) {}
  Point_2D operator=(const Point_2D &rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  Point_2D operator+(const Point_2D &rhs) const {
    return Point_2D(x + rhs.x, y + rhs.y);
  }
  Point_2D operator-(const Point_2D &rhs) const {
    return Point_2D(x - rhs.x, y - rhs.y);
  }
  Point_2D operator+=(const Point_2D &rhs) { return *this = *this + rhs; }
  Point_2D operator-=(const Point_2D &rhs) { return *this = *this - rhs; }
  Point_2D operator/(double n) const { return Point_2D(x / n, y / n); }
  Point_2D operator/=(double n) { return *this = *this / n; }
};
double sqr_add(const Point_2D &a) { return a.x * a.x + a.y * a.y; }
double sqr_minus(const Point_2D &a) { return a.x * a.x - a.y * a.y; }
double sqr_add_add(const Point_2D &a, const Point_2D &b) {
  return ((a.x * a.x + b.x * b.x) + (a.y * a.y + b.y * b.y)) / 2;
}
double sqr_add_minus(const Point_2D &a, const Point_2D &b) {
  return ((a.x * a.x + b.x * b.x) - (a.y * a.y + b.y * b.y)) / 2;
}
double sqr_minus_add(const Point_2D &a, const Point_2D &b) {
  return ((a.x * a.x - b.x * b.x) + (a.y * a.y - b.y * b.y)) / 2;
}
double sqr_minus_minus(const Point_2D &a, const Point_2D &b) {
  return ((a.x * a.x - b.x * b.x) - (a.y * a.y - b.y * b.y)) / 2;
}
Point_2D mid_point(const Point_2D &a, const Point_2D &b) { return (a + b) / 2; }
double inner_prod(const Point_2D &a, const Point_2D &b) {
  return a.x * b.x + a.y * b.y;
}
double outer_prod(const Point_2D &a, const Point_2D &b) {
  return a.x * b.y - a.y * b.x;
}
double distance(const Point_2D &a, const Point_2D &b) {
  return sqrt(sqr_add(a - b));
}
}  // namespace _Point_2D
using _Point_2D::Point_2D;
namespace _Circle {
using namespace _Point_2D;
struct Circle {
  Point_2D c;
  double d;
  Circle(const Point_2D &c = Point_2D(), double d = 0): c(c), d(d) {}
  Circle operator=(const Circle &rhs) {
    c = rhs.c;
    d = rhs.d;
    return *this;
  }
  bool is_covering(const Point_2D &a) { return distance(c, a) - d <= EPS; }
  bool on_circle(const Point_2D &a) { return abs(distance(c, a) - d) <= EPS; }
  bool in_circle(const Point_2D &a) { return is_covering(a) && !on_circle(a); }
  bool out_circle(const Point_2D &a) { return !is_covering(a); }
};
Circle get_circle(const Point_2D &a, const Point_2D &b) {
  return Circle(mid_point(a, b), distance(a, b) / 2);
}
Circle get_circle(const Point_2D &a, const Point_2D &b, const Point_2D &c) {
  Point_2D _a = b - a, _b = c - a;
  double _c = sqr_minus_add(b, a), _d = sqr_minus_add(c, a);
  Circle ret;
  ret.c = Point_2D((_b.y * _c - _a.y * _d) / outer_prod(_a, _b),
                   (_a.x * _d - _b.x * _c) / outer_prod(_a, _b));
  ret.d = distance(ret.c, a);
  return ret;
}
Circle minimum_coverage(int n, Point_2D a[]) {
  Circle ret(a[1]);
  for (int i = 2; i <= n; ++i)
    if (ret.out_circle(a[i])) {
      ret = Circle(a[i]);
      for (int j = 1; j < i; ++j) {
        if (ret.out_circle(a[j])) {
          ret = get_circle(a[i], a[j]);
          for (int k = 1; k < j; ++k)
            if (ret.out_circle(a[k])) { ret = get_circle(a[i], a[j], a[k]); }
        }
      }
    }
  return ret;
}
}  // namespace _Circle
using namespace _Circle;
Point_2D a[N];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
  random_shuffle(a + 1, a + n + 1);
  Circle ans = minimum_coverage(n, a);
  printf("%.10lf\n%.10lf %.10lf", ans.d, ans.c.x, ans.c.y);
  return 0;
}
