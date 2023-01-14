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
#define run_exec_(expressions, post_process) \
  {                                          \
    expressions;                             \
    post_process;                            \
  }
#define run_continue_(expressions) run_exec_(expressions, continue)
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
#define SCALA_FUNC(name, func_body) \
  data_t name() const func_body;    \
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
#define SELF_FUNC(name, func_body) \
  Point2 &do_##name() func_body;   \
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
  Point2 &do_rot(data_t theta) {
    data_t _x = x, _y = y;
    x = _x * cos(theta) - _y * sin(theta);
    y = _x * sin(theta) + _y * cos(theta);
    return *this;
  };
  friend Point2 rot(Point2 lhs, data_t theta) { return lhs.do_rot(theta); }
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
struct Polynomial2 {
  std::vector<Point2> vs;
  Polynomial2() {}
  explicit Polynomial2(size_t size_): vs(size_) {}
  explicit Polynomial2(const std::vector<Point2> &vs_): vs(vs_) {}
  friend std::istream &operator>>(std::istream &is, Polynomial2 &rhs) {
    for (std::vector<Point2>::iterator it = rhs.vs.begin(); it != rhs.vs.end();
         ++it)
      is >> *it;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Polynomial2 &rhs) {
    for (std::vector<Point2>::const_iterator it = rhs.vs.begin();
         it != rhs.vs.end() - 1;
         ++it)
      os << *it << ' ';
    return os << rhs.vs.back();
  }
  Polynomial2 &resort() {
    std::sort(vs.begin(), vs.end());
    return *this;
  }
  Polynomial2 &reunique() {
    resort();
    vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
    return *this;
  }
  Point2 &operator[](size_t x) { return vs[x]; }
  const Point2 &operator[](size_t x) const { return vs[x]; }
  std::vector<Point2>::const_iterator
  prev(std::vector<Point2>::const_iterator it) const {
    return --(it == vs.begin() ? it = vs.end() : it);
  }
  std::vector<Point2>::const_iterator
  next(std::vector<Point2>::const_iterator it) const {
    return ++it == vs.end() ? vs.begin() : it;
  }
  size_t prev(size_t idx) const { return idx == 0 ? vs.size() - 1 : idx - 1; }
  size_t next(size_t idx) const { return idx + 1 == vs.size() ? 0 : idx + 1; }
#define SCALA_FUNC(name, func_body) \
  data_t name() const func_body;    \
  friend data_t name(const Polynomial2 &lhs) { return lhs.name(); }
  SCALA_FUNC(circum, {
    data_t ret = dist_PP(vs[vs.size() - 1], vs[0]);
    for (size_t i = 0; i < vs.size() - 1; ++i) ret += dist_PP(vs[i], vs[i + 1]);
    return ret;
  })
  SCALA_FUNC(area, {
    data_t ret = cross_mul(vs[vs.size() - 1], vs[0]);
    for (size_t i = 0; i < vs.size() - 1; ++i)
      ret += cross_mul(vs[i], vs[i + 1]);
    return ret / 2;
  })
#undef SCALA_FUNC
  static const size_t inside = 3;
  static const size_t onendpoint = 2;
  static const size_t onborder = 1;
  static const size_t outside = 0;
  virtual size_t relation_P(const Point2 &p) const {
    for (std::vector<Point2>::const_iterator it = vs.begin(); it != vs.end();
         ++it)
      if (*it == p) return onendpoint;
    bool result = false;
    for (size_t i = 0; i < vs.size(); ++i) {
      Point2 now_p = vs[i], next_p = vs[next(i)];
      if (is_on_S(Line2(now_p, next_p), p)) return onborder;
      if (!is_greater(now_p.y, next_p.y)) std::swap(now_p, next_p);
      if (is_greater(p.y, now_p.y) || !is_greater(p.y, next_p.y)) continue;
      result ^= cross_sign(p, now_p, next_p) > 0;
    }
    return result ? inside : outside;
  }
  bool is_convex() const {
    bool flag[2] = {false, false};
    size_t sz = vs.size();
    if (sz < 3) return true;
    for (size_t i = 0, j = next(i), k = next(j); i < sz;
         ++i, j = next(j), k = next(k)) {
      ptrdiff_t sgn = cross_sign(vs[i], vs[j], vs[k]);
      if (sgn) flag[(sgn + 1) / 2] = true;
      if (flag[0] && flag[1]) return false;
    }
    return true;
  }
  uint_data_t cnt_intP_border() {
    uint_data_t ret = 0;
    for (size_t i = 0; i < vs.size(); ++i)
      ret += gcd(f2uint(std::abs(vs[i].x - vs[next(i)].x)),
                 f2uint(std::abs(vs[i].y - vs[next(i)].y)));
    return ret;
  }
  uint_data_t cnt_intP_inner() {
    return f2uint(area()) - cnt_intP_border() / 2 + 1;
  }
  Point2 mass_point() const {
    Point2 ret(0, 0);
    data_t area = 0;
    if (vs.size() == 0) return ret;
    if (vs.size() == 1) return vs[0];
    for (size_t i = 1; i < vs.size() - 1; ++i) {
      data_t tmp = cross(vs[0], vs[i], vs[i + 1]);
      if (is_zero(tmp)) continue;
      area += tmp;
      ret += (vs[0] + vs[i] + vs[i + 1]) * (tmp / 3);
    }
    if (!is_zero(area)) ret = ret / area;
    return ret;
  }
};
struct ConvexHull2: public Polynomial2 {
  ConvexHull2() {}
  explicit ConvexHull2(size_t size_): Polynomial2(size_) {}
  explicit ConvexHull2(const std::vector<Point2> &vs_,
                       bool inited = false,
                       bool strict = true)
    : Polynomial2(vs_) {
    if (!inited) strict ? init() : init_nonstrict();
  }
  friend std::istream &operator>>(std::istream &is, ConvexHull2 &rhs) {
    for (std::vector<Point2>::iterator it = rhs.vs.begin(); it != rhs.vs.end();
         ++it)
      is >> *it;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const ConvexHull2 &rhs) {
    for (std::vector<Point2>::const_iterator it = rhs.vs.begin();
         it != rhs.vs.end() - 1;
         ++it)
      os << *it << ' ';
    return os << rhs.vs.back();
  }
  ConvexHull2 &init() {
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return *this;
    resort();
    std::vector<Point2> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
      while (sz_cvh > 1 &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
      while (sz_cvh > t &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vs = cvh;
    return *this;
  }
  ConvexHull2 &init_nonstrict() {
    reunique();
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return *this;
    std::vector<Point2> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
      while (sz_cvh > 1 &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
      while (sz_cvh > t &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vs = cvh;
    return *this;
  }
  friend bool is_ins_cvh(const ConvexHull2 &cvhl, const ConvexHull2 &cvhr) {
    for (std::vector<Point2>::const_iterator it = cvhl.vs.begin();
         it != cvhl.vs.end();
         ++it)
      if (cvhr.relation_P(*it)) return false;
    for (std::vector<Point2>::const_iterator it = cvhr.vs.begin();
         it != cvhr.vs.end();
         ++it)
      if (cvhl.relation_P(*it)) return false;
    size_t n = cvhl.vs.size(), m = cvhr.vs.size();
    if (n > 1 && m > 1) {
      for (size_t l = 0, nextl = 1; l < n; nextl = cvhl.next(l = nextl))
        for (size_t r = 0, nextr = 1; r < m; nextr = cvhl.next(r = nextr))
          if (is_ins_SS(Line2(cvhl[l], cvhl[nextl]),
                        Line2(cvhr[r], cvhr[nextr])))
            return false;
    } else if (n == 1) {
      if (cvhl[0] == cvhr[0]) return false;
      if (m == 1) return true;
      return !is_on_S(Line2(cvhr[0], cvhr[1]), cvhl[0]);
    } else {
      if (is_on_S(Line2(cvhr[0], cvhr[1]), cvhr[0])) return false;
      if (m == 1) return true;
      return !is_ins_SS(Line2(cvhr[0], cvhr[1]), Line2(cvhr[0], cvhr[1]));
    }
    return true;
  }
  data_t diameter() const {
    size_t sz = vs.size();
    if (sz <= 1) return data_t(0);
    size_t is = 0;
    size_t js = 0;
    for (size_t k = 1; k < sz; ++k) {
      is = vs[k] < vs[is] ? k : is;
      js = vs[js] < vs[k] ? k : js;
    }
    size_t i = is;
    size_t j = js;
    data_t ret = dist_PP(vs[i], vs[j]);
    do {
      (++(cross_mul(vs[next(i)] - vs[i], vs[next(j)] - vs[j]) >= 0 ? j : i)) %=
        sz;
      ret = std::max(ret, dist_PP(vs[i], vs[j]));
    } while (i != is || j != js);
    return ret;
  }
  ConvexHull2 &do_minkowski_sum_nonstrict(const ConvexHull2 &rhs) {
    size_t n = vs.size(), m = rhs.vs.size();
    if (!m) return *this;
    if (!n) return *this = rhs;
    std::vector<Point2> result;
    result.reserve(n + m);
    size_t midxl = 0;
    for (size_t i = 1; i < n; ++i)
      if (vs[i] < vs[midxl]) midxl = i;
    size_t midxr = 0;
    for (size_t i = 1; i < m; ++i)
      if (rhs[i] < rhs[midxr]) midxr = i;
    bool fl = false, fr = false;
    for (size_t idxl = midxl, idxr = midxr;
         !(idxl == midxl && fl) || !(idxr == midxr && fr);) {
      Point2 diffl = vs[next(idxl)] - vs[idxl];
      Point2 diffr = rhs[rhs.next(idxr)] - rhs[idxr];
      bool f = !(idxl == midxl && fl) &&
               ((idxr == midxr && fr) || is_positive(cross_mul(diffl, diffr)));
      result.push_back(vs[idxl] + rhs[idxr] + (f ? diffl : diffr));
      (f ? idxl : idxr) = (f ? next(idxl) : rhs.next(idxr));
      (f ? fl : fr) |= !(f ? idxl : idxr);
    }
    vs = result;
    return *this;
  }
  friend ConvexHull2 minkowski_sum_nonstrict(ConvexHull2 poly,
                                             const ConvexHull2 &rhs) {
    return poly.do_minkowski_sum_nonstrict(rhs);
  }
  ConvexHull2 &do_minkowski_sum(const ConvexHull2 &rhs) {
    return do_minkowski_sum_nonstrict(rhs).init();
  }
  friend ConvexHull2 minkowski_sum(ConvexHull2 poly, const ConvexHull2 &rhs) {
    return poly.do_minkowski_sum(rhs);
  }
  ConvexHull2 &do_ins_CVHhP(const Line2 &l) {
    size_t sz = vs.size();
    std::vector<Point2> cvc;
    for (size_t i = 0; i < sz; ++i) {
      Point2 p1 = vs[i], p2 = vs[next(i)];
      ptrdiff_t d1 = cross_sign(l.l, l.r, p1), d2 = cross_sign(l.l, l.r, p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL(Line2(p1, p2), l));
    }
    vs = cvc;
    return *this;
  }
  friend ConvexHull2 ins_CVHhP(ConvexHull2 poly, const Line2 &l) {
    return poly.do_ins_CVHhP(l);
  }
};
bool ins_hP_check(const Line2 &u, const Line2 &v, const Line2 &w) {
  return w.is_include(ins_LL(u, v));
}
ConvexHull2 ins_hP(std::vector<Line2> vl) {
  std::sort(vl.begin(), vl.end());
  vl.erase(std::unique(vl.begin(), vl.end()), vl.end());
  if (vl.size() < 3) return ConvexHull2();
  std::deque<Line2> q;
  for (std::vector<Line2>::iterator it = vl.begin(); it != vl.end(); ++it) {
    if (it != vl.begin() && is_same_dir(*it, *(it - 1))) continue;
    while (q.size() > 1 && !ins_hP_check(*(q.rbegin() + 1), q.back(), *it))
      q.pop_back();
    while (q.size() > 1 && !ins_hP_check(*(q.begin() + 1), q.front(), *it))
      q.pop_front();
    q.push_back(*it);
  }
  while (q.size() > 2 && !ins_hP_check(*(q.rbegin() + 1), q.back(), q.front()))
    q.pop_back();
  while (q.size() > 2 && !ins_hP_check(*(q.begin() + 1), q.front(), q.back()))
    q.pop_front();
  std::vector<Point2> ret;
  for (size_t i = 0; i < q.size(); ++i)
    ret.push_back(ins_LL(q[i], q[(i + 1) % q.size()]));
  return ConvexHull2(ret, true);
}
}  // namespace geometry2d
using namespace geometry2d;
void solve(int t_) {
  int n;
  while ((cin >> n), ~n) {
    ConvexHull2 cvh(n);
    cin >> cvh;
    cvh.init();
    if (cvh.vs.size() < 3) run_continue_(cout << "0.00\n");
    size_t j = 1, k = 2;
    data_t ans = 0, tmp, new_tmp;
    for (size_t i = 0; i < cvh.vs.size(); ++i) {
      if (i == j) j = cvh.next(j);
      if (j == k) k = cvh.next(k);
      tmp = cross(cvh[i], cvh[j], cvh[k]);
      ans = std::max(ans, tmp);
      bool f = true;
      while (f) {
        f = false;
        if (is_greater(new_tmp = cross(cvh[i], cvh[j], cvh[cvh.next(k)]),
                       tmp)) {
          k = cvh.next(k);
          ans = std::max(ans, tmp = new_tmp);
          f = true;
        }
        if (is_greater(new_tmp = cross(cvh[i], cvh[cvh.next(j)], cvh[k]),
                       tmp)) {
          j = cvh.next(j);
          ans = std::max(ans, tmp = new_tmp);
          f = true;
        }
      }
    }
    cout << ans / 2 << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int i_ = 0;
  cout << fixed << setprecision(2);
  solve(i_);
  return 0;
}
