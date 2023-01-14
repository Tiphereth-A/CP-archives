#include <bits/stdc++.h>
using namespace std;
#define OPERATOR_OVERRIED_PAIR_(oper)                                 \
  template <typename Tp, typename Up>                                 \
  std::pair<Tp, Up> &operator oper##=(std::pair<Tp, Up> &lhs,         \
                                      const std::pair<Tp, Up> &rhs) { \
    lhs.first oper## = rhs.first;                                     \
    lhs.second oper## = rhs.second;                                   \
    return lhs;                                                       \
  }                                                                   \
  template <typename Tp, typename Up>                                 \
  std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs,              \
                                  const std::pair<Tp, Up> &rhs) {     \
    return lhs oper## = rhs;                                          \
  }
OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)
#undef OPERATOR_OVERRIED_PAIR_
template <typename Tp, typename Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <typename Tp>
using vc = std::vector<Tp>;
#define all_(a) (a).begin(), (a).end()
#define run_exec_(expressions, post_process) \
  {                                          \
    expressions;                             \
    post_process;                            \
  }
#define run_continue_(expressions) run_exec_(expressions, continue)
template <class Tp>
auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
template <typename Tp>
auto discretization(Tp &var) -> Tp {
  Tp d__(var);
  std::sort(d__.begin(), d__.end());
  d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
  for (auto &i : var)
    i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
  return d__;
};
template <typename Tp>
auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
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
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
  else
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  if (&os == &std::cerr) os << "]";
  return os;
}
const double EPS = 1e-6;
const double PI = acos(-1.0);
namespace calc_geo {
using data_t = double;
template <typename Tp>
using cont_t = std::vector<Tp>;
const data_t EPS = 1e-9;
ptrdiff_t sign(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
bool is_negative(data_t x) { return sign(x) & 2; }
bool is_zero(data_t x) { return !sign(x); }
bool is_positive(data_t x) { return (sign(x) + 1) & 2; }
ptrdiff_t comp(data_t lhs, data_t rhs) { return sign(lhs - rhs); }
bool is_less(data_t lhs, data_t rhs) { return is_negative(lhs - rhs); }
bool is_equal(data_t lhs, data_t rhs) { return is_zero(lhs - rhs); }
bool is_greater(data_t lhs, data_t rhs) { return is_positive(lhs - rhs); }
bool is_intersect(data_t l1, data_t r1, data_t l2, data_t r2) {
  if (l1 > r1) {
    auto tmp = l1;
    l1 = r1;
    r1 = tmp;
  }
  if (l2 > r2) {
    auto tmp = l2;
    l2 = r2;
    r2 = tmp;
  }
  return !(is_less(r1, l2) || is_less(r2, l1));
}
bool is_in_middle(data_t l, data_t mid, data_t r) {
  return is_equal(l, mid) || is_equal(r, mid) || ((l < mid) ^ (r < mid));
}
struct Point2 {
  using self = Point2;
  data_t x, y;
  Point2(data_t x = data_t{}, data_t y = data_t{}): x(x), y(y) {}
  friend std::istream &operator>>(std::istream &is, self &rhs) {
    return is >> rhs.x >> rhs.y;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &rhs) {
    return os << rhs.x << ' ' << rhs.y;
  }
  self &set_as_polar(data_t r, data_t theta) {
    return *this = {r * cos(theta), r * sin(theta)};
  }
  friend self lerp(const self &lhs, const self &rhs, data_t coord) {
    return lhs * coord + rhs * (1 - coord);
  }
  friend self mid_point(const self &lhs, const self &rhs) {
    return lerp(lhs, rhs, 0.5);
  }
#define SCALA_OP(op)               \
  self &operator op##=(data_t n) { \
    this->x op## = n;              \
    this->y op## = n;              \
    return *this;                  \
  }                                \
  self operator op(data_t n) const { return self(*this) op## = n; }
  SCALA_OP(+)
  SCALA_OP(-)
  SCALA_OP(*)
  SCALA_OP(/)
#undef SCALA_OP
#define VEC_OP(op)                         \
  self &operator op##=(const self & rhs) { \
    this->x op## = rhs.x;                  \
    this->y op## = rhs.y;                  \
    return *this;                          \
  }                                        \
  self operator op(const self &rhs) const { return self(*this) op## = rhs; }
  VEC_OP(+)
  VEC_OP(-)
#undef VEC_OP
  self operator-() const { return self{-x, -y}; }
  bool operator<(const self &rhs) const {
    auto c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  bool operator==(const self &rhs) const {
    return is_equal(x, rhs.x) && is_equal(y, rhs.y);
  }
  bool operator!=(const self &rhs) const { return !(*this == rhs); }
  friend data_t dot_mul(const self &lhs, const self &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend data_t cross_mul(const self &lhs, const self &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
#define SCALA_FUNC(name, func_body) \
  data_t name() const func_body;    \
  friend data_t name(const self &lhs) { return lhs.name(); }
  SCALA_FUNC(arg, { return atan2(y, x); })
  SCALA_FUNC(arg_2pi, {
    data_t tmp_ = arg();
    return is_negative(tmp_) ? tmp_ + 2 * acos(data_t{-1}) : tmp_;
  })
  SCALA_FUNC(norm, { return x * x + y * y; })
  SCALA_FUNC(abs, { return sqrt(norm()); })
  static constexpr int QUAD_STATE[3][3] = {{5, 6, 7}, {4, 0, 0}, {3, 2, 1}};
  int quad() const { return QUAD_STATE[sign(y) + 1][sign(x) + 1]; };
  friend int quad(const self &lhs) { return lhs.quad(); }
#undef SCALA_FUNC
#define SELF_FUNC(name, func_body) \
  self &do_##name() func_body;     \
  friend self name(self lhs) { return lhs.do_##name(); }
  SELF_FUNC(rotate90, {
    data_t tmp = x;
    x = -y;
    y = tmp;
    return *this;
  })
  SELF_FUNC(rotate180, {
    x = -x;
    y = -y;
    return *this;
  })
  SELF_FUNC(rotate270, {
    data_t tmp = y;
    y = -x;
    x = tmp;
    return *this;
  })
  SELF_FUNC(unit, { return *this /= abs(); })
#undef SELF_FUNC
  self &do_rotate(data_t theta) {
    data_t _x = x, _y = y;
    x = _x * cos(theta) - _y * sin(theta);
    y = _x * sin(theta) + _y * cos(theta);
    return *this;
  };
  friend self rotate(self lhs, data_t theta) { return lhs.do_rotate(theta); }
};
data_t dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return hypot(lhs.x - rhs.x, lhs.y - rhs.y);
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
struct Triangle {
  using self = Triangle;
  using point_t = Point2;
  point_t A, B, C;
  Triangle() = default;
  Triangle(const point_t &a, const point_t &b, const point_t &c)
    : A(a), B(b), C(c) {}
  Triangle(const data_t &a_x,
           const data_t &a_y,
           const data_t &b_x,
           const data_t &b_y,
           const data_t &c_x,
           const data_t &c_y)
    : A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}
  friend std::istream &operator>>(std::istream &is, self &rhs) {
    return is >> rhs.A >> rhs.B >> rhs.C;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &rhs) {
    return os << rhs.A << ' ' << rhs.B << ' ' << rhs.C;
  }
  data_t area() const { return std::abs(cross(A, B, C)) / 2; }
  point_t average_w(data_t wA, data_t wB, data_t wC) const {
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
  Point2 center_O() const {
    data_t a2 = (B - C).norm(), b2 = (C - A).norm(), c2 = (A - B).norm();
    return average_w(
      a2 * (b2 + c2 - a2), b2 * (c2 + a2 - b2), c2 * (a2 + b2 - c2));
  }
  Point2 center_G() const { return average_w(1, 1, 1); }
  Point2 center_H() const {
    data_t a2 = (B - C).norm(), b2 = (C - A).norm(), c2 = (A - B).norm();
    data_t a4 = a2 * a2, b4 = b2 * b2, c4 = c2 * c2;
    return average_w(a4 - b4 - c4 + 2 * b2 * c2,
                     b4 - c4 - a4 + 2 * c2 * a2,
                     c4 - a4 - b4 + 2 * a2 * b2);
  }
  Point2 center_N() const { return mid_point(center_O(), center_H()); }
  Point2 center_X() const {
    data_t s3 = sqrt(data_t{3}), r = radius_I(), R = radius_O(),
           s = ((A - B).abs() + (B - C).abs() + (C - A).abs()) / 2;
    return center_I() * (s3 * (r * r + 2 * r * R + s * s)) +
           center_O() * (-6 * r * (s3 * R - 2 * s)) +
           center_G() * (-2 * r * (s3 * r + 3 * s));
  }
};
struct Line2 {
  using self = Line2;
  using point_t = Point2;
  point_t l, r;
  Line2() = default;
  Line2(const point_t &start_, const point_t &end_): l(start_), r(end_) {}
  Line2(const data_t &start_x,
        const data_t &start_y,
        const data_t &end_x,
        const data_t &end_y)
    : l(start_x, start_y), r(end_x, end_y) {}
  friend std::istream &operator>>(std::istream &is, self &rhs) {
    return is >> rhs.l >> rhs.r;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &rhs) {
    return os << rhs.l << ' ' << rhs.r;
  }
  friend bool operator<(const self &lhs, const self &rhs) {
    if (is_same_dir(lhs, rhs)) return rhs.is_include(lhs.l);
    auto vl = lhs.direction();
    auto vr = rhs.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_positive(cross_mul(vl, vr));
  }
  data_t slope() const { return (r.y - l.y) / (r.x - l.x); }
  data_t slope_inv() const { return (r.x - l.x) / (r.y - l.y); }
  data_t intercept_v() const { return r.y - r.x * slope(); }
  data_t intercept_h() const { return r.x - r.y * slope_inv(); }
  data_t lerp_y(data_t x) const { return l.y + (x - l.x) * slope(); }
  data_t lerp_x(data_t y) const { return l.x + (y - l.y) * slope_inv(); }
  friend bool is_parallel(const self &lhs, const self &rhs) {
    return is_zero(cross_mul(lhs.direction(), rhs.direction()));
  }
  friend bool is_same_dir(const self &lhs, const self &rhs) {
    return is_parallel(lhs, rhs) &&
           is_positive(dot_mul(lhs.direction(), rhs.direction()));
  }
  point_t direction() const { return r - l; }
  bool is_include(const point_t &p) const {
    return is_positive(cross(l, r, p));
  }
  self &do_push(data_t eps = 1e-8) {
    point_t delta = direction().do_rotate90().do_unit();
    delta *= eps;
    l += delta;
    r += delta;
    return *this;
  }
  friend self push(self line, data_t eps = 1e-8) { return line.do_push(eps); }
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
  return std::min({dist_PS(s1.l, s2),
                   dist_PS(s1.r, s2),
                   dist_PS(s2.l, s1),
                   dist_PS(s2.r, s1)});
}
struct Circle2 {
  using self = Circle2;
  using point_t = Point2;
  point_t o;
  data_t r;
  Circle2() = default;
  Circle2(const point_t &c, data_t r): o(c), r(r) {}
  Circle2(const data_t &c_x, const data_t &c_y, data_t r_)
    : o(c_x, c_y), r(r_) {}
  friend std::istream &operator>>(std::istream &is, self &rhs) {
    return is >> rhs.o >> rhs.r;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &rhs) {
    return os << rhs.o << ' ' << rhs.r;
  }
  static const size_t lying_out = 4;
  static const size_t touch_ex = 3;
  static const size_t intersect_2p = 2;
  static const size_t touch_in = 1;
  static const size_t lying_in = 0;
  friend size_t relation_C(const Circle2 &c1, const Circle2 &c2) {
    data_t d = dist_PP(c1.o, c2.o);
    if (is_greater(d, c1.r + c2.r)) return lying_out;
    if (is_equal(d, c1.r + c2.r)) return touch_ex;
    if (is_greater(d, std::abs(c1.r - c2.r))) return intersect_2p;
    if (is_equal(d, std::abs(c1.r - c2.r))) return touch_in;
    return lying_in;
  }
  static const size_t inside = 2;
  static const size_t on_border = 1;
  static const size_t outside = 0;
  size_t relation_P(const point_t &p) const {
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
cont_t<Point2> ins_CL(const Circle2 &c, const Line2 &l1) {
  if (is_greater(
        std::abs(cross_mul(c.o - l1.l, l1.r - l1.l) / dist_PP(l1.l, l1.r)),
        c.r))
    return {};
  data_t x = dot_mul(l1.l - c.o, l1.r - l1.l), y = (l1.r - l1.l).norm(),
         d = std::max(x * x - y * ((l1.l - c.o).norm() - c.r * c.r), data_t{0});
  Point2 m = l1.l - (l1.r - l1.l) * (x / y), dr = (l1.r - l1.l) * (sqrt(d) / y);
  return {m - dr, m + dr};
}
cont_t<Point2> ins_CC(const Circle2 &c1, const Circle2 &c2) {
  assert(!is_equal(c1.o.x, c2.o.x) || !is_equal(c1.o.y, c2.o.y) ||
         !is_equal(c1.r, c2.r));
  auto state = relation_C(c1, c2);
  if (state == Circle2::lying_in || state == Circle2::lying_out) return {};
  data_t d = std::min(dist_PP(c1.o, c2.o), c1.r + c2.r);
  data_t y = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d),
         x = sqrt(c1.r * c1.r - y * y);
  Point2 dr = (c2.o - c1.o).do_unit();
  Point2 q1 = c1.o + dr * y, q2 = dr.do_rotate90() * x;
  return {q1 - q2, q1 + q2};
}
cont_t<Circle2> make_C_rPP(data_t r, const Point2 &p1, const Point2 &p2) {
  cont_t<Point2> ps = ins_CC({p1, r}, {p2, r});
  cont_t<Circle2> ret;
  for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
  return ret;
}
cont_t<Circle2> make_C_rPL(data_t r, const Point2 &p, const Line2 &l) {
  double dis = dist_PL(p, l);
  if (is_positive(dis - r * 2)) return {};
  Point2 dir = l.direction();
  dir *= r / dir.abs();
  Point2 dirl = rotate90(dir), dirr = rotate270(dir);
  if (is_zero(dis)) return {{p + dirl, r}, {p + dirr, r}};
  Circle2 c{p, r};
  cont_t<Point2> ps = ins_CL(c, {l.l + dirl, l.r + dirl});
  if (ps.size() == 0) ps = ins_CL(c, {l.l + dirr, l.r + dirr});
  cont_t<Circle2> ret;
  for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
  return ret;
}
cont_t<Circle2> make_C_rLL(data_t r, const Line2 &l1, const Line2 &l2) {
  if (is_parallel(l1, l2)) return {};
  Point2 dir1 = l1.direction(), dir2 = l2.direction();
  dir1 *= r / dir1.abs();
  dir2 *= r / dir2.abs();
  Point2 dirl1 = rotate90(dir1), dirr1 = rotate270(dir1),
         dirl2 = rotate90(dir2), dirr2 = rotate270(dir2);
  Line2 u1 = Line2{l1.l + dirl1, l1.r + dirl1};
  Line2 u2 = Line2{l1.l + dirr1, l1.r + dirr1};
  Line2 v1 = Line2{l2.l + dirl2, l2.r + dirl2};
  Line2 v2 = Line2{l2.l + dirr2, l2.r + dirr2};
  return {{ins_LL(u1, v1), r},
          {ins_LL(u1, v2), r},
          {ins_LL(u2, v1), r},
          {ins_LL(u2, v2), r}};
}
cont_t<Circle2> make_C_rCC(data_t r, const Circle2 &c1, const Circle2 &c2) {
  cont_t<Point2> ps = ins_CC({c1.o, c1.r + r}, {c2.o, c2.r + r});
  cont_t<Circle2> ret;
  for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
  return ret;
}
Point2 inv_P(const Circle2 &c, const Point2 &p) {
  Point2 v = p - c.o;
  return c.o + v * (c.r * c.r / v.norm());
}
Circle2 inv_C2C(const Circle2 &c, const Circle2 &c2) {
  Point2 v = (c2.o - c.o).do_unit();
  Point2 p1 = c2.o + v * c2.r, p2 = c2.o - v * c2.r;
  return {mid_point(p1, p2), dist_PP(p1, p2) / 2};
}
Line2 inv_C2L(const Circle2 &c, const Point2 &p) {
  Point2 v = (p - c.o).do_rotate90();
  return {inv_P(c, p + v), inv_P(c, p - v)};
}
Circle2 inv_L(const Circle2 &c, const Line2 &l) {
  Point2 p1 = inv_P(c, l.l), p2 = inv_P(c, l.r);
  Point2 o2 = Triangle{p1, p2, c.o}.center_O();
  return {o2, dist_PP(c.o, o2)};
}
cont_t<Point2> tan_CP(const Circle2 &c, const Point2 &p) {
  Point2 v = p - c.o;
  data_t x = v.norm(), d = x - c.r * c.r;
  if (is_negative(d)) return {};
  Point2 q1 = c.o + v * (c.r * c.r / x);
  Point2 q2 = v.do_rotate90() * (c.r * sqrt(d) / x);
  return {q1 - q2, q1 + q2};
}
cont_t<Line2> extan_CC(const Circle2 &c1, const Circle2 &c2) {
  assert(!is_equal(c1.o.x, c2.o.x) || !is_equal(c1.o.y, c2.o.y));
  cont_t<Line2> ret;
  if (is_equal(c1.r, c2.r)) {
    Point2 dr = (c2.o - c1.o).do_unit().do_rotate90() * c1.r;
    ret.emplace_back(c1.o + dr, c2.o + dr);
    ret.emplace_back(c1.o - dr, c2.o - dr);
  } else {
    Point2 p = (c2.o * c1.r - c1.o * c2.r) / (c1.r - c2.r);
    cont_t<Point2> ps = tan_CP(c1, p), qs = tan_CP(c2, p);
    for (size_t i = 0; i < std::min(ps.size(), qs.size()); ++i)
      ret.emplace_back(ps[i], qs[i]);
  }
  return ret;
}
cont_t<Line2> intan_CC(const Circle2 &c1, const Circle2 &c2) {
  assert(!is_equal(c1.o.x, c2.o.x) || !is_equal(c1.o.y, c2.o.y));
  cont_t<Line2> ret;
  Point2 p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
  cont_t<Point2> ps = tan_CP(c1, p), qs = tan_CP(c2, p);
  for (size_t i = 0; i < std::min(ps.size(), qs.size()); ++i)
    ret.emplace_back(ps[i], qs[i]);
  return ret;
}
data_t area_CT(data_t r, const Point2 &p1, const Point2 &p2) {
  cont_t<Point2> is = ins_CL({{0, 0}, r}, {p1, p2});
  if (is.empty()) return r * r * ang_PP(p1, p2) / 2;
  bool b1 = is_greater(p1.norm(), r * r), b2 = is_greater(p2.norm(), r * r);
  if (b1 && b2) {
    if (!is_positive(dot_mul(p1 - is[0], p2 - is[0])) &&
        !is_positive(dot_mul(p1 - is[0], p2 - is[0])))
      return r * r * (ang_PP(p1, is[0]) + ang_PP(is[1], p2)) / 2 +
             cross_mul(is[0], is[1]) / 2;
    else return r * r * ang_PP(p1, p2) / 2;
  }
  if (b1) return (r * r * ang_PP(p1, is[0]) + cross_mul(is[0], p2)) / 2;
  if (b2) return (cross_mul(p1, is[1]) + r * r * ang_PP(is[1], p2)) / 2;
  return cross_mul(p1, p2) / 2;
}
Circle2 min_cover_C(const cont_t<Point2> &vp) {
  Circle2 ret{vp.front(), 0};
  size_t sz = vp.size();
  for (size_t i = 1; i < sz; ++i) {
    if (ret.relation_P(vp[i]) != Circle2::outside) continue;
    ret = Circle2{vp[i], 0};
    for (size_t j = 0; j < i; ++j) {
      if (ret.relation_P(vp[j]) != Circle2::outside) continue;
      ret = Circle2{mid_point(vp[i], vp[j]), dist_PP(vp[i], vp[j]) / 2};
      for (size_t k = 0; k < j; ++k) {
        if (ret.relation_P(vp[k]) != Circle2::outside) continue;
        Point2 o = Triangle{vp[i], vp[j], vp[k]}.center_O();
        ret = Circle2{o, dist_PP(o, vp[i])};
      }
    }
  }
  return ret;
}
}  // namespace calc_geo
using namespace calc_geo;
auto solve([[maybe_unused]] int t_) -> void {
  string s;
  while (cin >> s) {
    if (s == "CircumscribedCircle") {
      Triangle t;
      cin >> t;
      Point2 o = t.center_O();
      data_t r = t.radius_O();
      cout << '(' << o.x << ',' << o.y << ',' << r << ")\n";
      continue;
    }
    if (s == "InscribedCircle") {
      Triangle t;
      cin >> t;
      Point2 i = t.center_I();
      data_t r = t.radius_I();
      cout << '(' << i.x << ',' << i.y << ',' << r << ")\n";
      continue;
    }
    if (s == "TangentLineThroughPoint") {
      Circle2 c;
      Point2 p;
      cin >> c >> p;
      vc<Point2> tps = tan_CP(c, p);
      if (tps.size() == 0) run_continue_(cout << "[]\n");
      Point2 d1 = Line2{p, tps[0]}.direction(),
             d2 = Line2{p, tps[1]}.direction();
      data_t angle1 = atan2(d1.y, d1.x) / PI * 180;
      data_t angle2 = atan2(d2.y, d2.x) / PI * 180;
      if (angle1 < 0) angle1 += 180;
      if (angle1 >= 180) angle1 -= 180;
      if (angle2 < 0) angle2 += 180;
      if (angle2 >= 180) angle2 -= 180;
      if (is_equal(angle1, angle2))
        run_continue_(cout << '[' << angle1 << "]\n");
      if (angle1 > angle2) swap(angle1, angle2);
      cout << '[' << angle1 << ',' << angle2 << "]\n";
      continue;
    }
    if (s == "CircleThroughAPointAndTangentToALineWithRadius") {
      Point2 p;
      Line2 l;
      data_t r;
      cin >> p >> l >> r;
      vc<Circle2> cs = make_C_rPL(r, p, l);
      if (cs.size() == 0) run_continue_(cout << "[]\n");
      if (cs[1].o < cs[0].o) swap(cs[0], cs[1]);
      if (cs[0].o == cs[1].o)
        run_continue_(cout << "[(" << cs[0].o.x << ',' << cs[0].o.y << ")]\n");
      cout << "[(" << cs[0].o.x << ',' << cs[0].o.y << "),(" << cs[1].o.x << ','
           << cs[1].o.y << ")]\n";
      continue;
    }
    if (s == "CircleTangentToTwoLinesWithRadius") {
      Line2 l1, l2;
      data_t r;
      cin >> l1 >> l2 >> r;
      vc<Circle2> cs = make_C_rLL(r, l1, l2);
      if (cs.size() == 0) run_continue_(cout << "[]\n");
      sort(all_(cs), [](const Circle2 &lhs, const Circle2 &rhs) {
        return lhs.o < rhs.o;
      });
      cout << "[(" << cs[0].o.x << ',' << cs[0].o.y << "),(" << cs[1].o.x << ','
           << cs[1].o.y << "),(" << cs[2].o.x << ',' << cs[2].o.y << "),("
           << cs[3].o.x << ',' << cs[3].o.y << ")]\n";
      continue;
    }
    if (s == "CircleTangentToTwoDisjointCirclesWithRadius") {
      Circle2 c1, c2;
      data_t r;
      cin >> c1 >> c2 >> r;
      vc<Circle2> cs = make_C_rCC(r, c1, c2);
      if (cs.size() == 0) run_continue_(cout << "[]\n");
      if (cs[1].o < cs[0].o) swap(cs[0], cs[1]);
      if (cs[0].o == cs[1].o)
        run_continue_(cout << "[(" << cs[0].o.x << ',' << cs[0].o.y << ")]\n");
      cout << "[(" << cs[0].o.x << ',' << cs[0].o.y << "),(" << cs[1].o.x << ','
           << cs[1].o.y << ")]\n";
      continue;
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  cout << fixed << setprecision(6);
  solve(i_);
  return 0;
}
