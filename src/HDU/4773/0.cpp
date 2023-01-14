#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;
#define for_(i, l, r) for (ptrdiff_t i = (l), i##end = (r); i <= i##end; ++i)
#define all_(a) (a).begin(), (a).end()
#define run_exec_(expressions, post_process) \
  {                                          \
    expressions;                             \
    post_process;                            \
  }
#define run_return_void_(expressions) run_exec_(expressions, return)
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  if (&os == &std::cerr) return os << "(" << p.first << ", " << p.second << ")";
  return os << p.first << " " << p.second;
}
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Container &x) {
  if (&os == &std::cerr) os << "[";
  if (&os == &std::cerr)
    for (typename Container::const_iterator it = x.begin(); it != x.end() - 1;
         ++it)
      os << *it << ", ";
  else
    for (typename Container::const_iterator it = x.begin(); it != x.end() - 1;
         ++it)
      os << *it << ' ';
  os << x.back();
  if (&os == &std::cerr) os << "]";
  return os;
}
namespace geometry2d {
const int QUAD__[9] = {5, 6, 7, 4, 0, 0, 3, 2, 1};
typedef double data_t;
typedef unsigned long long uint_data_t;
const data_t EPS = 1e-8;
const data_t PI = std::acos(data_t(-1));
uint_data_t f2uint(data_t x) { return uint_data_t(x + EPS); }
uint_data_t gcd(uint_data_t m, uint_data_t n) {
  return n == 0 ? m : gcd(n, m % n);
}
ptrdiff_t sign(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
bool is_negative(data_t x) { return sign(x) & 2; }
bool is_zero(data_t x) { return !sign(x); }
bool is_positive(data_t x) { return (sign(x) + 1) & 2; }
ptrdiff_t comp(data_t lhs, data_t rhs) { return sign(lhs - rhs); }
bool is_less(data_t lhs, data_t rhs) { return is_negative(lhs - rhs); }
bool is_equal(data_t lhs, data_t rhs) { return is_zero(lhs - rhs); }
bool is_greater(data_t lhs, data_t rhs) { return is_positive(lhs - rhs); }
ptrdiff_t comp_rerr(data_t lhs, data_t rhs) {
  return sign((lhs - rhs) / std::abs(lhs));
}
bool is_less_rerr(data_t lhs, data_t rhs) {
  return is_negative((lhs - rhs) / std::abs(lhs));
}
bool is_equal_rerr(data_t lhs, data_t rhs) {
  return is_zero((lhs - rhs) / std::abs(lhs));
}
bool is_greater_rerr(data_t lhs, data_t rhs) {
  return is_positive((lhs - rhs) / std::abs(lhs));
}
bool is_intersect(data_t l1, data_t r1, data_t l2, data_t r2) {
  if (l1 > r1) std::swap(l1, r1);
  if (l2 > r2) std::swap(l2, r2);
  return !(is_less(r1, l2) || is_less(r2, l1));
}
bool is_in_middle(data_t l, data_t mid, data_t r) {
  return is_equal(l, mid) || is_equal(r, mid) || ((l < mid) ^ (r < mid));
}
struct Point2 {
  data_t x, y;
  Point2(data_t x = data_t(0), data_t y = data_t(0)): x(x), y(y) {}
  friend std::istream &operator>>(std::istream &is, Point2 &rhs) {
    return is >> rhs.x >> rhs.y;
  }
  friend std::ostream &operator<<(std::ostream &os, const Point2 &rhs) {
    return os << rhs.x << ' ' << rhs.y;
  }
  Point2 &set_as_polar(data_t r, data_t theta) {
    return *this = Point2(r * cos(theta), r * sin(theta));
  }
  friend Point2 lerp(const Point2 &lhs, const Point2 &rhs, data_t coord) {
    return lhs * coord + rhs * (1 - coord);
  }
  friend Point2 mid_point(const Point2 &lhs, const Point2 &rhs) {
    return lerp(lhs, rhs, 0.5);
  }
#define SCALA_OP(op)                 \
  Point2 &operator op##=(data_t n) { \
    this->x op## = n;                \
    this->y op## = n;                \
    return *this;                    \
  }                                  \
  Point2 operator op(data_t n) const { return Point2(*this) op## = n; }
  SCALA_OP(+)
  SCALA_OP(-)
  SCALA_OP(*)
  SCALA_OP(/)
#undef SCALA_OP
#define VEC_OP(op)                              \
  Point2 &operator op##=(const Point2 & rhs) {  \
    this->x op## = rhs.x;                       \
    this->y op## = rhs.y;                       \
    return *this;                               \
  }                                             \
  Point2 operator op(const Point2 &rhs) const { \
    return Point2(*this) op## = rhs;            \
  }
  VEC_OP(+)
  VEC_OP(-)
#undef VEC_OP
  Point2 operator-() const { return Point2(-x, -y); }
  bool operator<(const Point2 &rhs) const {
    ptrdiff_t c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  bool operator==(const Point2 &rhs) const {
    return is_equal(x, rhs.x) && is_equal(y, rhs.y);
  }
  bool operator!=(const Point2 &rhs) const { return !(*this == rhs); }
  friend data_t dot_mul(const Point2 &lhs, const Point2 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend data_t cross_mul(const Point2 &lhs, const Point2 &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
#define SCALA_FUNC(name, ...)      \
  data_t name() const __VA_ARGS__; \
  friend data_t name(const Point2 &lhs) { return lhs.name(); }
  SCALA_FUNC(arg, { return atan2(y, x); })
  SCALA_FUNC(arg2pi, {
    data_t tmp_ = arg();
    return is_negative(tmp_) ? tmp_ + 2 * PI : tmp_;
  })
  SCALA_FUNC(norm, { return x * x + y * y; })
  SCALA_FUNC(abs, { return sqrt(norm()); })
  int quad() const { return QUAD__[(sign(y) + 1) * 3 + sign(x) + 1]; }
  friend int quad(const Point2 &lhs) { return lhs.quad(); }
#undef SCALA_FUNC
#define SELF_FUNC(name, ...)       \
  Point2 &do_##name() __VA_ARGS__; \
  friend Point2 name(Point2 lhs) { return lhs.do_##name(); }
  SELF_FUNC(rot90, {
    data_t tmp = x;
    x = -y;
    y = tmp;
    return *this;
  })
  SELF_FUNC(rot180, {
    x = -x;
    y = -y;
    return *this;
  })
  SELF_FUNC(rot270, {
    data_t tmp = y;
    y = -x;
    x = tmp;
    return *this;
  })
  SELF_FUNC(unit, { return *this /= abs(); })
#undef SELF_FUNC
#define SELF_FUNC1(name, rhs_type, rhs, ...)            \
  Point2 &do_##name(const rhs_type &rhs) __VA_ARGS__;   \
  friend Point2 name(Point2 lhs, const rhs_type &rhs) { \
    return lhs.do_##name(rhs);                          \
  }
  SELF_FUNC1(rot, data_t, theta, {
    data_t _x = x, _y = y;
    x = _x * cos(theta) - _y * sin(theta);
    y = _x * sin(theta) + _y * cos(theta);
    return *this;
  })
#undef SELF_FUNC1
};
data_t dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return std::sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x) +
                   (lhs.y - rhs.y) * (lhs.y - rhs.y));
}
data_t sqr_dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y);
}
data_t cross(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}
ptrdiff_t cross_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return sign(cross(p1, p2, p3));
}
data_t dot(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y);
}
ptrdiff_t dot_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return sign(dot(p1, p2, p3));
}
bool is_in_middle(Point2 a, Point2 m, Point2 b) {
  return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y);
}
data_t ang_PP(const Point2 &p1, const Point2 &p2) {
  return atan2(cross_mul(p1, p2), dot_mul(p1, p2));
}
data_t ang2pi_PP(const Point2 &p1, const Point2 &p2) {
  data_t res = ang_PP(p1, p2);
  return is_negative(res) ? res + 2 * PI : res;
}
struct Line2 {
  Point2 l, r;
  Line2() {}
  Line2(const Point2 &start_, const Point2 &end_): l(start_), r(end_) {}
  Line2(const data_t &start_x,
        const data_t &start_y,
        const data_t &end_x,
        const data_t &end_y)
    : l(start_x, start_y), r(end_x, end_y) {}
  friend std::istream &operator>>(std::istream &is, Line2 &rhs) {
    return is >> rhs.l >> rhs.r;
  }
  friend std::ostream &operator<<(std::ostream &os, const Line2 &rhs) {
    return os << rhs.l << ' ' << rhs.r;
  }
  friend bool operator<(const Line2 &lhs, const Line2 &rhs) {
    if (is_same_dir(lhs, rhs)) return rhs.is_include(lhs.l);
    Point2 vl = lhs.direction();
    Point2 vr = rhs.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_positive(cross_mul(vl, vr));
  }
  friend bool operator==(const Line2 &lhs, const Line2 &rhs) {
    return lhs.l == rhs.l && lhs.r == rhs.r;
  }
  data_t slope() const { return (r.y - l.y) / (r.x - l.x); }
  data_t slope_inv() const { return (r.x - l.x) / (r.y - l.y); }
  data_t intercept_v() const { return r.y - r.x * slope(); }
  data_t intercept_h() const { return r.x - r.y * slope_inv(); }
  data_t lerp_y(data_t x) const { return l.y + (x - l.x) * slope(); }
  data_t lerp_x(data_t y) const { return l.x + (y - l.y) * slope_inv(); }
  friend bool is_parallel(const Line2 &lhs, const Line2 &rhs) {
    return is_zero(cross_mul(lhs.direction(), rhs.direction()));
  }
  friend bool is_same_dir(const Line2 &lhs, const Line2 &rhs) {
    return is_parallel(lhs, rhs) &&
           is_positive(dot_mul(lhs.direction(), rhs.direction()));
  }
  Point2 direction() const { return r - l; }
  bool is_include(const Point2 &p) const { return is_positive(cross(l, r, p)); }
  bool passes_through(const Point2 &p) const { return is_zero(cross(l, r, p)); }
  Line2 &do_push(data_t dist) {
    Point2 delta = direction().do_rot90().do_unit();
    delta *= dist;
    l += delta;
    r += delta;
    return *this;
  }
  friend Line2 push(Line2 line, data_t dist) { return line.do_push(dist); }
};
bool is_ins_LL(const Line2 &l1, const Line2 &l2) {
  return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r));
}
Point2 ins_LL(const Line2 &l1, const Line2 &l2) {
  data_t a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}
bool is_ins_SS(const Line2 &l1, const Line2 &l2) {
  return is_intersect(l1.l.x, l1.r.x, l2.l.x, l2.r.x) &&
         is_intersect(l1.l.y, l1.r.y, l2.l.y, l2.r.y) &&
         cross_sign(l1.l, l1.r, l2.l) * cross_sign(l1.l, l1.r, l2.r) <= 0 &&
         cross_sign(l2.l, l2.r, l1.l) * cross_sign(l2.l, l2.r, l1.r) <= 0;
}
bool is_ins_SS_strict(const Line2 &s1, const Line2 &s2) {
  return cross_sign(s1.l, s1.r, s2.l) * cross_sign(s1.l, s1.r, s2.r) < 0 &&
         cross_sign(s2.l, s2.r, s1.l) * cross_sign(s2.l, s2.r, s1.r) < 0;
}
Point2 proj(const Line2 &l1, const Point2 &p) {
  Point2 dir = l1.direction();
  return l1.l + dir * (dot_mul(dir, p - l1.l) / dir.norm());
}
Point2 reflect(const Line2 &l1, const Point2 &p) { return proj(l1, p) * 2 - p; }
bool is_on_same_L(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return is_zero(cross(p1, p2, p3));
}
bool is_on_S(const Line2 &s1, const Point2 &p) {
  return is_on_same_L(s1.l, s1.r, p) && is_in_middle(s1.l, p, s1.r);
}
bool is_on_S_strict(const Line2 &s1, const Point2 &p) {
  return cross_sign(s1.l, s1.r, p) == 0 &&
         sign(dot_mul(p - s1.l, s1.l - s1.r)) *
             sign(dot_mul(p - s1.r, s1.l - s1.r)) <
           0;
}
data_t dist_PL(const Point2 &p, const Line2 &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  return dist_PP(p, proj(s1, p));
}
data_t dist_PS(const Point2 &p, const Line2 &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  Point2 h = proj(s1, p);
  if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
  return std::min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}
data_t dist_SS(const Line2 &s1, const Line2 &s2) {
  if (is_ins_SS(s1, s2)) return 0;
  return std::min(std::min(dist_PS(s1.l, s2), dist_PS(s1.r, s2)),
                  std::min(dist_PS(s2.l, s1), dist_PS(s2.r, s1)));
}
struct Triangle {
  Point2 A, B, C;
  Triangle() {}
  Triangle(const Point2 &a, const Point2 &b, const Point2 &c)
    : A(a), B(b), C(c) {}
  Triangle(const data_t &a_x,
           const data_t &a_y,
           const data_t &b_x,
           const data_t &b_y,
           const data_t &c_x,
           const data_t &c_y)
    : A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}
  friend std::istream &operator>>(std::istream &is, Triangle &rhs) {
    return is >> rhs.A >> rhs.B >> rhs.C;
  }
  friend std::ostream &operator<<(std::ostream &os, const Triangle &rhs) {
    return os << rhs.A << ' ' << rhs.B << ' ' << rhs.C;
  }
  friend bool operator==(const Triangle &lhs, const Triangle &rhs) {
    return lhs.A == rhs.A && lhs.B == rhs.B && lhs.C == rhs.C;
  }
  data_t area() const { return std::abs(cross(A, B, C)) / 2; }
  Point2 average_w(data_t wA, data_t wB, data_t wC) const {
    return (A * wA + B * wB + C * wC) / (wA + wB + wC);
  }
  bool is_acute() const {
    return is_positive(dot(A, B, C)) && is_positive(dot(B, C, A)) &&
           is_positive(dot(C, A, B));
  }
  bool is_right() const {
    return is_zero(dot(A, B, C)) || is_zero(dot(B, C, A)) ||
           is_zero(dot(C, A, B));
  }
  bool is_obtuse() const {
    return is_negative(dot(A, B, C)) || is_negative(dot(B, C, A)) ||
           is_negative(dot(C, A, B));
  }
  data_t radius_I() const {
    data_t ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
    return 2 * area() / (ab + bc + ca);
  }
  data_t radius_O() const {
    data_t ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
    return ab * bc * ca / (4 * area());
  }
  Point2 center_I() const {
    return average_w((B - C).abs(), (C - A).abs(), (A - B).abs());
  }
  Point2 center_E() const {
    return average_w(-((B - C).abs()), (C - A).abs(), (A - B).abs());
  }
  Point2 center_G() const { return average_w(1, 1, 1); }
  Point2 center_O() const {
    Point2 p1 = mid_point(B, C), p2 = mid_point(C, A);
    return ins_LL(Line2(p1, p1 + (B - C).do_rot90()),
                  Line2(p2, p2 + (C - A).do_rot90()));
  }
  Point2 center_H() const {
    return ins_LL(Line2(A, A + (B - C).do_rot90()),
                  Line2(B, B + (C - A).do_rot90()));
  }
  Point2 center_N() const { return mid_point(center_O(), center_H()); }
  Point2 center_X() const {
    data_t s3 = sqrt(data_t(3)), r = radius_I(), R = radius_O(),
           s = ((A - B).abs() + (B - C).abs() + (C - A).abs()) / 2;
    return center_I() * (s3 * (r * r + 2 * r * R + s * s)) +
           center_O() * (-6 * r * (s3 * R - 2 * s)) +
           center_G() * (-2 * r * (s3 * r + 3 * s));
  }
};
data_t area_T_abc(data_t a, data_t b, data_t c) {
  return std::sqrt((a + (b + c)) * (c - (a - b)) * (c + (a - b)) *
                   (a + (b - c))) /
         4;
}
struct Circle2 {
  Point2 o;
  data_t r;
  Circle2() {}
  Circle2(const Point2 &c, data_t r): o(c), r(r) {}
  Circle2(const data_t &c_x, const data_t &c_y, data_t r_)
    : o(c_x, c_y), r(r_) {}
  friend std::istream &operator>>(std::istream &is, Circle2 &rhs) {
    return is >> rhs.o >> rhs.r;
  }
  friend std::ostream &operator<<(std::ostream &os, const Circle2 &rhs) {
    return os << rhs.o << ' ' << rhs.r;
  }
  friend bool operator==(const Circle2 &lhs, const Circle2 &rhs) {
    return lhs.o == rhs.o && lhs.r == rhs.r;
  }
  data_t area(data_t angle = PI * 2) const { return angle * r * r / 2; }
  data_t crown_area(data_t angle = PI * 2) const {
    return (angle - std::sin(angle)) * r * r / 2;
  }
  data_t arc(data_t angle = PI * 2) const { return angle * r; }
  static const size_t lying_out = 4;
  static const size_t touch_ex = 3;
  static const size_t intersect_2p = 2;
  static const size_t touch_in = 1;
  static const size_t lying_in = 0;
  size_t relation_C(const Circle2 &c2) const {
    data_t d = dist_PP(o, c2.o);
    if (is_greater(d, r + c2.r)) return lying_out;
    if (is_equal(d, r + c2.r)) return touch_ex;
    if (is_greater(d, std::abs(r - c2.r))) return intersect_2p;
    if (is_equal(d, std::abs(r - c2.r))) return touch_in;
    return lying_in;
  }
  static const size_t inside = 2;
  static const size_t on_border = 1;
  static const size_t outside = 0;
  size_t relation_P(const Point2 &p) const {
    data_t d = dist_PP(o, p);
    if (is_less(d, r)) return inside;
    if (is_equal(d, r)) return on_border;
    return outside;
  }
  static const size_t intersect = 2;
  static const size_t tagante = 1;
  static const size_t otherwise = 0;
  size_t relation_L(const Line2 &l) const {
    data_t d = dist_PL(o, l);
    if (is_less(d, r)) return intersect;
    if (is_equal(d, r)) return tagante;
    return outside;
  }
  size_t relation_S(const Line2 &s) const {
    data_t d = dist_PS(o, s);
    if (is_less(d, r)) return intersect;
    if (is_equal(d, r)) return tagante;
    return otherwise;
  }
};
std::vector<Point2> ins_CL(const Circle2 &c, const Line2 &l1) {
  if (is_greater(
        std::abs(cross_mul(c.o - l1.l, l1.r - l1.l) / dist_PP(l1.l, l1.r)),
        c.r))
    return std::vector<Point2>();
  data_t x = dot_mul(l1.l - c.o, l1.r - l1.l), y = l1.direction().norm(),
         d = std::max(x * x - y * ((l1.l - c.o).norm() - c.r * c.r), data_t(0));
  Point2 m = l1.l - l1.direction() * (x / y),
         dr = l1.direction() * (sqrt(d) / y);
  std::vector<Point2> ret;
  ret.push_back(m - dr);
  ret.push_back(m + dr);
  return ret;
}
std::vector<Point2> ins_CC(const Circle2 &c1, const Circle2 &c2) {
  assert(!is_equal(c1.o.x, c2.o.x) || !is_equal(c1.o.y, c2.o.y) ||
         !is_equal(c1.r, c2.r));
  size_t state = c1.relation_C(c2);
  if (state == Circle2::lying_in || state == Circle2::lying_out)
    return std::vector<Point2>();
  data_t d = std::min(dist_PP(c1.o, c2.o), c1.r + c2.r);
  data_t y = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d),
         x = sqrt(c1.r * c1.r - y * y);
  Point2 dr = (c2.o - c1.o).do_unit();
  Point2 q1 = c1.o + dr * y, q2 = dr.do_rot90() * x;
  std::vector<Point2> ret;
  ret.push_back(q1 - q2);
  ret.push_back(q1 + q2);
  return ret;
}
Circle2 make_C_PPP(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  Point2 o = Triangle(p1, p2, p3).center_O();
  return Circle2(o, dist_PP(o, p1));
}
Point2 inv_P2P(const Circle2 &c, const Point2 &p) {
  Point2 v = p - c.o;
  return c.o + v * (c.r * c.r / v.norm());
}
Circle2 inv_C2C(const Circle2 &c, const Circle2 &c2) {
  Point2 v = (c2.o - c.o).do_unit();
  Point2 p1 = inv_P2P(c, c2.o + v * c2.r), p2 = inv_P2P(c, c2.o - v * c2.r);
  return Circle2(mid_point(p1, p2), dist_PP(p1, p2) / 2);
}
Line2 inv_C2L(const Circle2 &c, const Circle2 &c2) {
  Point2 v = (c2.o - c.o).do_rot90();
  return Line2(inv_P2P(c, c2.o + v), inv_P2P(c, c2.o - v));
}
Circle2 inv_L2C(const Circle2 &c, const Line2 &l) {
  Point2 p1 = inv_P2P(c, l.l), p2 = inv_P2P(c, l.r);
  return make_C_PPP(p1, p2, c.o);
}
std::vector<Point2> tan_CP(const Circle2 &c, const Point2 &p) {
  Point2 v = p - c.o;
  data_t x = v.norm(), d = x - c.r * c.r;
  if (is_negative(d)) return std::vector<Point2>();
  Point2 q1 = c.o + v * (c.r * c.r / x);
  Point2 q2 = v.do_rot90() * (c.r * sqrt(d) / x);
  std::vector<Point2> ret;
  ret.push_back(q1 - q2);
  ret.push_back(q1 + q2);
  return ret;
}
std::vector<Line2> extan_CC(const Circle2 &c1, const Circle2 &c2) {
  if (is_equal(c1.o.x, c2.o.x) && is_equal(c1.o.y, c2.o.y))
    return std::vector<Line2>();
  std::vector<Line2> ret;
  if (is_equal(c1.r, c2.r)) {
    Point2 dr = (c2.o - c1.o).do_unit().do_rot90() * c1.r;
    ret.push_back(Line2(c1.o + dr, c2.o + dr));
    ret.push_back(Line2(c1.o - dr, c2.o - dr));
  } else {
    Point2 p = (c2.o * c1.r - c1.o * c2.r) / (c1.r - c2.r);
    std::vector<Point2> ps = tan_CP(c1, p), qs = tan_CP(c2, p);
    for (size_t i = 0; i < std::min(ps.size(), qs.size()); ++i)
      ret.push_back(Line2(ps[i], qs[i]));
  }
  return ret;
}
std::vector<Line2> intan_CC(const Circle2 &c1, const Circle2 &c2) {
  if (is_equal(c1.o.x, c2.o.x) && is_equal(c1.o.y, c2.o.y))
    return std::vector<Line2>();
  std::vector<Line2> ret;
  Point2 p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
  std::vector<Point2> ps = tan_CP(c1, p), qs = tan_CP(c2, p);
  for (size_t i = 0; i < std::min(ps.size(), qs.size()); ++i)
    ret.push_back(Line2(ps[i], qs[i]));
  return ret;
}
}  // namespace geometry2d
using namespace geometry2d;
void solve(int t_) {
  Circle2 c1, c2;
  Point2 p;
  cin >> c1 >> c2 >> p;
  Circle2 invc(p, 5);
  Circle2 ic1 = inv_C2C(invc, c1), ic2 = inv_C2C(invc, c2);
  if (ic2.r > ic1.r) swap(ic1, ic2);
  std::vector<Line2> vec = extan_CC(ic1, ic2), vec2 = intan_CC(ic1, ic2);
  vec.insert(vec.end(), all_(vec2));
  sort(all_(vec));
  vec.erase(unique(all_(vec)), vec.end());
  vec2.clear();
  if (vec.empty()) run_return_void_(cout << "0\n");
  for_(i, 0, vec.size() - 1)
    if (!(vec[i].is_include(ic1.o) ^ vec[i].is_include(ic2.o)) &&
        !(vec[i].is_include(ic1.o) ^ vec[i].is_include(p)))
      vec2.push_back(vec[i]);
  cout << vec2.size() << '\n';
  for_(i, 0, vec2.size() - 1) cout << inv_L2C(invc, vec2[i]) << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int i_ = 0;
  cout << fixed << setprecision(8);
  int t_;
  std::cin >> t_;
  for (i_ = 1; i_ <= t_; ++i_) solve(i_);
  return 0;
}
