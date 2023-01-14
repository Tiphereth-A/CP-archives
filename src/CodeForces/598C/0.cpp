#include <bits/stdc++.h>
using namespace std;
template <typename Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define all_(a) (a).begin(), (a).end()
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
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
namespace calc_geo {
using data_t = long double;
template <typename Tp>
using cont_t = std::vector<Tp>;
const data_t PI = acos(data_t{-1});
constexpr data_t EPS = 1e-18;
constexpr data_t DATA_MAX = DBL_MAX;
constexpr ptrdiff_t sign(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
constexpr bool is_negative(data_t x) { return sign(x) & 2; }
constexpr bool is_zero(data_t x) { return !sign(x); }
constexpr bool is_positive(data_t x) { return (sign(x) + 1) & 2; }
constexpr ptrdiff_t comp(data_t lhs, data_t rhs) { return sign(lhs - rhs); }
constexpr bool is_less(data_t lhs, data_t rhs) {
  return is_negative(lhs - rhs);
}
constexpr bool is_equal(data_t lhs, data_t rhs) { return is_zero(lhs - rhs); }
constexpr bool is_greater(data_t lhs, data_t rhs) {
  return is_positive(lhs - rhs);
}
constexpr bool is_intersect(data_t l1, data_t r1, data_t l2, data_t r2) {
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
constexpr bool is_in_middle(data_t l, data_t mid, data_t r) {
  return is_equal(l, mid) || is_equal(r, mid) || ((l < mid) ^ (r < mid));
}
struct Point2 {
  using self = Point2;
  data_t x, y;
  constexpr Point2(data_t x = data_t{}, data_t y = data_t{}): x(x), y(y) {}
  friend istream &operator>>(istream &is, self &rhs) {
    return is >> rhs.x >> rhs.y;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    return os << rhs.x << ' ' << rhs.y;
  }
  constexpr self &set_as_polar(data_t r, data_t theta) {
    return *this = {r * cos(theta), r * sin(theta)};
  }
  friend constexpr self lerp(const self &lhs, const self &rhs, data_t coord) {
    return lhs * coord + rhs * (1 - coord);
  }
  friend constexpr self mid_point(const self &lhs, const self &rhs) {
    return lerp(lhs, rhs, 0.5);
  }
#define SCALA_OP(op)                         \
  constexpr self &operator op##=(data_t n) { \
    this->x op## = n;                        \
    this->y op## = n;                        \
    return *this;                            \
  }                                          \
  constexpr self operator op(data_t n) const { return self(*this) op## = n; }
  SCALA_OP(+)
  SCALA_OP(-)
  SCALA_OP(*)
  SCALA_OP(/)
#undef SCALA_OP
#define VEC_OP(op)                                    \
  constexpr self &operator op##=(const self & rhs) {  \
    this->x op## = rhs.x;                             \
    this->y op## = rhs.y;                             \
    return *this;                                     \
  }                                                   \
  constexpr self operator op(const self &rhs) const { \
    return self(*this) op## = rhs;                    \
  }
  VEC_OP(+)
  VEC_OP(-)
#undef VEC_OP
  constexpr self operator-() const { return self{-x, -y}; }
  constexpr bool operator<(const self &rhs) const {
    auto c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  constexpr bool operator==(const self &rhs) const {
    return is_equal(x, rhs.x) && is_equal(y, rhs.y);
  }
  friend constexpr data_t dot_mul(const self &lhs, const self &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend constexpr data_t cross_mul(const self &lhs, const self &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
#define SCALA_FUNC(name, func_body)      \
  constexpr auto name() const func_body; \
  friend constexpr auto name(const self &lhs) { return lhs.name(); }
  SCALA_FUNC(arg, {
    data_t tmp_ = atan2(y, x);
    return is_negative(tmp_) ? tmp_ + 2 * PI : tmp_;
  })
  SCALA_FUNC(norm, { return x * x + y * y; })
  SCALA_FUNC(abs, { return sqrt(norm()); })
  static constexpr int QUAD_STATE[3][3] = {{5, 6, 7}, {4, 0, 0}, {3, 2, 1}};
  SCALA_FUNC(quad, { return QUAD_STATE[sign(y) + 1][sign(x) + 1]; })
#undef SCALA_FUNC
#define SELF_FUNC(name, func_body)       \
  constexpr self &do_##name() func_body; \
  friend constexpr self name(self lhs) { return lhs.do_##name(); }
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
  constexpr self &do_rotate(data_t theta) {
    data_t _x = x, _y = y;
    x = _x * cos(theta) - _y * sin(theta);
    y = _x * sin(theta) + _y * cos(theta);
    return *this;
  };
  friend constexpr self rotate(self lhs, data_t theta) {
    return lhs.do_rotate(theta);
  }
};
constexpr data_t dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return hypot(lhs.x - rhs.x, lhs.y - rhs.y);
}
constexpr data_t sqr_dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y);
}
constexpr data_t cross(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}
constexpr ptrdiff_t
cross_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return sign(cross(p1, p2, p3));
}
constexpr bool is_in_middle(Point2 a, Point2 m, Point2 b) {
  return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y);
}
constexpr data_t ang_PP(const Point2 &p1, const Point2 &p2) {
  return atan2(cross_mul(p1, p2), dot_mul(p1, p2));
}
struct Triangle {
  using self = Triangle;
  using point_t = Point2;
  point_t A, B, C;
  constexpr Triangle(const point_t &a = point_t{},
                     const point_t &b = point_t{},
                     const point_t &c = point_t{})
    : A(a), B(b), C(c) {}
  constexpr Triangle(const data_t &a_x,
                     const data_t &a_y,
                     const data_t &b_x,
                     const data_t &b_y,
                     const data_t &c_x,
                     const data_t &c_y)
    : A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}
  friend istream &operator>>(istream &is, self &rhs) {
    return is >> rhs.A >> rhs.B >> rhs.C;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    return os << rhs.A << ' ' << rhs.B << ' ' << rhs.C;
  }
  constexpr data_t area() const { return abs(cross(A, B, C)) / 2; }
  constexpr point_t average_w(data_t wA, data_t wB, data_t wC) const {
    return (A * wA + B * wB + C * wC) / (wA + wB + wC);
  }
  constexpr data_t radius_I() const {
    data_t ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
    return 2 * area() / (ab + bc + ca);
  }
  constexpr data_t radius_O() const {
    data_t ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
    return ab * bc * ca / (4 * area());
  }
  constexpr Point2 center_I() const {
    return average_w((B - C).abs(), (C - A).abs(), (A - B).abs());
  }
  constexpr Point2 center_E() const {
    return average_w(-((B - C).abs()), (C - A).abs(), (A - B).abs());
  }
  constexpr Point2 center_O() const {
    data_t a2 = (B - C).norm(), b2 = (C - A).norm(), c2 = (A - B).norm();
    return average_w(
      a2 * (b2 + c2 - a2), b2 * (c2 + a2 - b2), c2 * (a2 + b2 - c2));
  }
  constexpr Point2 center_G() const { return average_w(1, 1, 1); }
  constexpr Point2 center_H() const {
    data_t a2 = (B - C).norm(), b2 = (C - A).norm(), c2 = (A - B).norm();
    data_t a4 = a2 * a2, b4 = b2 * b2, c4 = c2 * c2;
    return average_w(a4 - b4 - c4 + 2 * b2 * c2,
                     b4 - c4 - a4 + 2 * c2 * a2,
                     c4 - a4 - b4 + 2 * a2 * b2);
  }
  constexpr Point2 center_N() const {
    return mid_point(center_O(), center_H());
  }
  constexpr Point2 center_X() const {
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
  constexpr Line2(const point_t &start_ = point_t{},
                  const point_t &end_ = point_t{})
    : l(start_), r(end_) {}
  constexpr Line2(const data_t &start_x,
                  const data_t &start_y,
                  const data_t &end_x,
                  const data_t &end_y)
    : l(start_x, start_y), r(end_x, end_y) {}
  friend istream &operator>>(istream &is, self &rhs) {
    return is >> rhs.l >> rhs.r;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    return os << rhs.l << ' ' << rhs.r;
  }
  constexpr friend bool operator<(const self &lhs, const self &rhs) {
    if (is_same_dir(lhs, rhs)) return rhs.is_include(lhs.l);
    auto vl = lhs.direction();
    auto vr = rhs.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_positive(cross_mul(vl, vr));
  }
  constexpr data_t slope() const { return (r.y - l.y) / (r.x - l.x); }
  constexpr data_t slope_inv() const { return (r.x - l.x) / (r.y - l.y); }
  constexpr data_t intercept_v() const { return r.y - r.x * slope(); }
  constexpr data_t intercept_h() const { return r.x - r.y * slope_inv(); }
  constexpr data_t lerp_y(data_t x) const { return l.y + (x - l.x) * slope(); }
  constexpr data_t lerp_x(data_t y) const {
    return l.x + (y - l.y) * slope_inv();
  }
  friend constexpr bool is_parallel(const self &lhs, const self &rhs) {
    return is_zero(cross_mul(lhs.direction(), rhs.direction()));
  }
  friend constexpr bool is_same_dir(const self &lhs, const self &rhs) {
    return is_parallel(lhs, rhs) &&
           is_positive(dot_mul(lhs.direction(), rhs.direction()));
  }
  constexpr point_t direction() const { return r - l; }
  constexpr bool is_include(const point_t &p) const {
    return is_positive(cross(l, r, p));
  }
  constexpr self &do_push(data_t eps = 1e-8) {
    point_t delta = direction().do_rotate90().do_unit();
    delta *= eps;
    l += delta;
    r += delta;
    return *this;
  }
  friend constexpr self push(self line, data_t eps = 1e-8) {
    return line.do_push(eps);
  }
};
constexpr bool is_ins_LL(const Line2 &l1, const Line2 &l2) {
  return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r));
}
constexpr Point2 ins_LL(const Line2 &l1, const Line2 &l2) {
  data_t a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}
constexpr bool is_ins_SS(const Line2 &l1, const Line2 &l2) {
  return is_intersect(l1.l.x, l1.r.x, l2.l.x, l2.r.x) &&
         is_intersect(l1.l.y, l1.r.y, l2.l.y, l2.r.y) &&
         cross_sign(l1.l, l1.r, l2.l) * cross_sign(l1.l, l1.r, l2.r) <= 0 &&
         cross_sign(l2.l, l2.r, l1.l) * cross_sign(l2.l, l2.r, l1.r) <= 0;
}
constexpr bool is_ins_SS_strict(const Line2 &s1, const Line2 &s2) {
  return cross_sign(s1.l, s1.r, s2.l) * cross_sign(s1.l, s1.r, s2.r) < 0 &&
         cross_sign(s2.l, s2.r, s1.l) * cross_sign(s2.l, s2.r, s1.r) < 0;
}
constexpr Point2 proj(const Line2 &l1, const Point2 &p) {
  Point2 dir = l1.direction();
  return l1.l + dir * (dot_mul(dir, p - l1.l) / dir.norm());
}
constexpr Point2 reflect(const Line2 &l1, const Point2 &p) {
  return proj(l1, p) * 2 - p;
}
constexpr bool is_on_S(const Line2 &s1, const Point2 &p) {
  return is_zero(cross(s1.l, s1.r, p)) && is_in_middle(s1.l, p, s1.r);
}
constexpr bool is_on_S_strict(const Line2 &s1, const Point2 &p) {
  return cross_sign(s1.l, s1.r, p) == 0 &&
         sign(dot_mul(p - s1.l, s1.l - s1.r)) *
             sign(dot_mul(p - s1.r, s1.l - s1.r)) <
           0;
}
constexpr data_t dist_PPS(const Line2 &s1, const Point2 &p) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  Point2 h = proj(s1, p);
  if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
  return min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}
constexpr data_t dist_SS(const Line2 &s1, const Line2 &s2) {
  if (is_ins_SS(s1, s2)) return 0;
  return min({dist_PPS(s1, s2.l),
              dist_PPS(s1, s2.r),
              dist_PPS(s2, s1.l),
              dist_PPS(s2, s1.r)});
}
struct Circle2 {
  using self = Circle2;
  using point_t = Point2;
  point_t o;
  data_t r;
  constexpr Circle2(const point_t &c, data_t r): o(c), r(r) {}
  constexpr Circle2(const data_t &c_x, const data_t &c_y, data_t r_)
    : o(c_x, c_y), r(r_) {}
  friend istream &operator>>(istream &is, self &rhs) {
    return is >> rhs.o >> rhs.r;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    return os << rhs.o << ' ' << rhs.r;
  }
  static const size_t lying_out = 4;
  static const size_t touch_ex = 3;
  static const size_t intersect_2p = 2;
  static const size_t touch_in = 1;
  static const size_t lying_in = 0;
  friend constexpr size_t insection_type(const Circle2 &c1, const Circle2 &c2) {
    data_t d = dist_PP(c1.o, c2.o);
    if (is_greater(d, c1.r + c2.r)) return self::lying_out;
    if (is_equal(d, c1.r + c2.r)) return self::touch_ex;
    if (is_greater(d, abs(c1.r - c2.r))) return self::intersect_2p;
    if (is_equal(d, abs(c1.r - c2.r))) return self::touch_in;
    return self::lying_in;
  }
  static const size_t inside = 2;
  static const size_t on_boarder = 1;
  static const size_t outside = 0;
  constexpr size_t is_containing(const point_t &p) const {
    data_t d = dist_PP(o, p);
    if (is_less(d, r)) return self::inside;
    if (is_equal(d, r)) return self::on_boarder;
    return self::outside;
  }
};
cont_t<Point2> ins_CL(const Circle2 &c, const Line2 &l1) {
  if (is_greater(abs(cross_mul(c.o - l1.l, l1.r - l1.l) / dist_PP(l1.l, l1.r)),
                 c.r))
    return {};
  data_t x = dot_mul(l1.l - c.o, l1.r - l1.l), y = (l1.r - l1.l).norm(),
         d = max(x * x - y * ((l1.l - c.o).norm() - c.r * c.r), data_t{0});
  Point2 m = l1.l - (l1.r - l1.l) * (x / y), dr = (l1.r - l1.l) * (sqrt(d) / y);
  return {m - dr, m + dr};
}
cont_t<Point2> ins_CC(const Circle2 &c1, const Circle2 &c2) {
  assert(!is_equal(c1.o.x, c2.o.x) || !is_equal(c1.o.y, c2.o.y) ||
         !is_equal(c1.r, c2.r));
  auto state = insection_type(c1, c2);
  if (state == Circle2::lying_in || state == Circle2::lying_out) return {};
  data_t d = min(dist_PP(c1.o, c2.o), c1.r + c2.r);
  data_t y = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d),
         x = sqrt(c1.r * c1.r - y * y);
  Point2 dr = (c2.o - c1.o).do_unit();
  Point2 q1 = c1.o + dr * y, q2 = dr.do_rotate90() * x;
  return {q1 - q2, q1 + q2};
}
constexpr Point2 inv_P(const Circle2 &c, const Point2 &p) {
  Point2 v = p - c.o;
  return c.o + v * (c.r * c.r / v.norm());
}
constexpr Circle2 inv_C2C(const Circle2 &c, const Circle2 &c2) {
  Point2 v = (c2.o - c.o).do_unit();
  Point2 p1 = c2.o + v * c2.r, p2 = c2.o - v * c2.r;
  return {mid_point(p1, p2), dist_PP(p1, p2) / 2};
}
constexpr Line2 inv_C2L(const Circle2 &c, const Point2 &p) {
  Point2 v = (p - c.o).do_rotate90();
  return {inv_P(c, p + v), inv_P(c, p - v)};
}
constexpr Circle2 inv_L(const Circle2 &c, const Line2 &l) {
  Point2 p1 = inv_P(c, l.l), p2 = inv_P(c, l.r);
  Point2 o2 = Triangle{p1, p2, c.o}.center_O();
  return {o2, dist_PP(c.o, o2)};
}
cont_t<Point2> tan_CP(const Circle2 &c, const Point2 &p) {
  Point2 v = p - c.o;
  data_t x = v.norm(), d = x - c.r * c.r;
  if (!is_positive(d)) return {};
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
struct Polynomial2 {
  using self = Polynomial2;
  using point_t = Point2;
  cont_t<point_t> vertice;
  Polynomial2(const cont_t<point_t> &_vertice): vertice(_vertice) {}
  friend istream &operator>>(istream &is, self &rhs) {
    for (auto &i : rhs.vertice) is >> i;
    return is;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    for (auto it = rhs.vertice.begin(); it != rhs.vertice.end() - 1; ++it)
      os << *it << ' ';
    return os << rhs.vertice.back();
  }
  self &resort() {
    std::sort(vertice.begin(), vertice.end());
    return *this;
  }
  self &reunique() {
    resort();
    vertice.erase(std::unique(vertice.begin(), vertice.end()), vertice.end());
    return *this;
  }
  point_t &operator[](size_t x) { return vertice[x]; }
  const point_t &operator[](size_t x) const { return vertice[x]; }
#define SCALA_FUNC(name, func_body) \
  auto name() const func_body;      \
  friend auto name(const self &lhs) { return lhs.name(); }
  SCALA_FUNC(circum, {
    data_t result{};
    size_t sz = vertice.size();
    for (size_t i = 0; i < sz; ++i)
      result += dist_PP(vertice[i], vertice[(i + 1) % sz]);
    return result;
  })
  SCALA_FUNC(area, {
    data_t result{};
    size_t sz = vertice.size();
    for (size_t i = 0; i < sz; ++i)
      result += cross_mul(vertice[i], vertice[(i + 1) % sz]);
    return result / 2;
  })
  SCALA_FUNC(convex_diameter, {
    size_t sz = vertice.size();
    if (sz <= 1) return data_t{};
    size_t is = 0;
    size_t js = 0;
    for (size_t k = 1; k < sz; ++k) {
      is = vertice[k] < vertice[is] ? k : is;
      js = vertice[js] < vertice[k] ? k : js;
    }
    size_t i = is;
    size_t j = js;
    data_t ret = dist_PP(vertice[i], vertice[j]);
    do {
      (++(cross_mul(vertice[(i + 1) % sz] - vertice[i],
                    vertice[(j + 1) % sz] - vertice[j]) >= 0 ?
            j :
            i)) %= sz;
      ret = std::max(ret, dist_PP(vertice[i], vertice[j]));
    } while (i != is || j != js);
    return ret;
  })
#undef SCALA_FUNC
  static const size_t inside = 2;
  static const size_t on_boarder = 1;
  static const size_t outside = 0;
  size_t is_containing(const point_t &p) const {
    bool result = 0;
    size_t sz = vertice.size();
    for (size_t i = 0; i < sz; ++i) {
      point_t now_p = vertice[i], next_p = vertice[(i + 1) % sz];
      if (is_on_S({now_p, next_p}, p)) return self::on_boarder;
      if (!is_greater(now_p.y, next_p.y)) std::swap(now_p, next_p);
      if (is_greater(p.y, now_p.y) || !is_greater(p.y, next_p.y)) continue;
      result ^= cross_sign(p, now_p, next_p) > 0;
    }
    return result ? self::inside : self::outside;
  }
  size_t is_containing_cvh(const point_t &p) const {
    if (is_positive(cross_mul(vertice.back(), p))) return self::outside;
    auto it = std::lower_bound(vertice.begin(),
                               vertice.end(),
                               p,
                               [](const point_t &lhs, const point_t &rhs) {
                                 return is_positive(cross_mul(lhs, rhs)) ||
                                        (is_zero(cross_mul(lhs, rhs)) &&
                                         lhs.norm() < rhs.norm());
                               });
    return is_equal(std::abs(cross_mul(*(it - 1), p)) +
                      std::abs(cross_mul(p, *it)) +
                      std::abs(cross(p, *(it - 1), *it)),
                    std::abs(cross_mul(*(it - 1), *it))) ?
             self::inside :
             self::outside;
  }
#define SELF_FUNC(name, func_body) \
  self &do_##name() func_body;     \
  friend self name(self lhs) { return lhs.do_##name(); }
  SELF_FUNC(convex_hull, {
    ptrdiff_t sz = vertice.size();
    if (sz <= 1) return *this;
    resort();
    cont_t<point_t> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vertice[i++])
      while (sz_cvh > 1 &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vertice[i]) <= 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vertice[i--])
      while (sz_cvh > t &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vertice[i]) <= 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vertice = cvh;
    return *this;
  })
  SELF_FUNC(convex_hull_nonstrict, {
    reunique();
    ptrdiff_t sz = vertice.size();
    if (sz <= 1) return *this;
    cont_t<point_t> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vertice[i++])
      while (sz_cvh > 1 &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vertice[i]) < 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vertice[i--])
      while (sz_cvh > t &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vertice[i]) < 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vertice = cvh;
    return *this;
  })
#undef SELF_FUNC
  self &do_convex_cut(const point_t &q1, const point_t &q2) {
    size_t sz = vertice.size();
    cont_t<point_t> cvc;
    for (size_t i = 0; i < sz; ++i) {
      point_t p1 = vertice[i], p2 = vertice[(i + 1) % sz];
      ptrdiff_t d1 = cross_sign(q1, q2, p1), d2 = cross_sign(q1, q2, p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, {q1, q2}));
    }
    vertice = cvc;
    return *this;
  }
  friend self convex_cut(self poly, const point_t &q1, const point_t &q2) {
    return poly.do_convex_cut(q1, q2);
  }
};
data_t min_dist(const cont_t<Point2> &vp, ptrdiff_t l, ptrdiff_t r) {
  data_t ret = DATA_MAX;
  if (r - l <= 5) {
    for (ptrdiff_t i = l; i < r; ++i)
      for (ptrdiff_t j = l; j < i; ++j)
        ret = std::min(ret, dist_PP(vp[i], vp[j]));
    return ret;
  }
  ptrdiff_t mid = r - (r - l) / 2;
  ret = min(min_dist(vp, l, mid), min_dist(vp, mid, r));
  cont_t<Point2> q;
  for (ptrdiff_t i = l; i < r; ++i)
    if (std::abs(vp[i].x - vp[mid].x) <= ret) q.push_back(vp[i]);
  std::sort(q.begin(), q.end(), [](const auto &lhs, const auto &rhs) -> bool {
    return lhs.y < rhs.y;
  });
  for (ptrdiff_t i = 1; i < (ptrdiff_t)q.size(); ++i)
    for (ptrdiff_t j = i - 1; ~j && q[j].y >= q[i].y - ret; --j)
      ret = std::min(ret, dist_PP(q[i], q[j]));
  return ret;
}
Circle2 min_cover_C(const cont_t<Point2> &vp) {
  Circle2 ret{vp.front(), 0};
  size_t sz = vp.size();
  for (size_t i = 1; i < sz; ++i) {
    if (ret.is_containing(vp[i]) != Circle2::outside) continue;
    ret = Circle2{vp[i], 0};
    for (size_t j = 0; j < i; ++j) {
      if (ret.is_containing(vp[j]) != Circle2::outside) continue;
      ret = Circle2{mid_point(vp[i], vp[j]), dist_PP(vp[i], vp[j]) / 2};
      for (size_t k = 0; k < j; ++k) {
        if (ret.is_containing(vp[k]) != Circle2::outside) continue;
        Point2 o = Triangle{vp[i], vp[j], vp[k]}.center_O();
        ret = Circle2{o, dist_PP(o, vp[i])};
      }
    }
  }
  return ret;
}
Polynomial2 ins_hP(cont_t<Line2> vl) {
  auto check = [](const Line2 &u, const Line2 &v, const Line2 &w) -> bool {
    return w.is_include(ins_LL(u, v));
  };
  std::sort(vl.begin(), vl.end());
  deque<Line2> q;
  for (auto it = vl.begin(); it != vl.end(); ++it) {
    if (it != vl.begin() && is_same_dir(*it, *(it - 1))) continue;
    while (q.size() > 1 && !check(*(q.rbegin() + 1), q.back(), *it))
      q.pop_back();
    while (q.size() > 1 && !check(*(q.begin() + 1), q.front(), *it))
      q.pop_front();
    q.push_back(*it);
  }
  while (q.size() > 2 && !check(*(q.rbegin() + 1), q.back(), q.front()))
    q.pop_back();
  while (q.size() > 2 && !check(*(q.begin() + 1), q.front(), q.back()))
    q.pop_front();
  cont_t<Point2> ret;
  for (size_t i = 0; i < q.size(); ++i)
    ret.push_back(ins_LL(q[i], q[(i + 1) % q.size()]));
  return ret;
}
}  // namespace calc_geo
using namespace calc_geo;
struct Node {
  int id;
  Line2 l;
  Node(int id = 0, data_t lx = 0, data_t ly = 0, data_t rx = 0, data_t ry = 0)
    : id(id), l(lx, ly, rx, ry) {}
  bool operator<(const Node &rhs) const { return l < rhs.l; }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  read_var_(int, n);
  vc<Node> vl;
  vl.reserve(n);
  for_(i, 1, n, x, y) {
    cin >> x >> y;
    vl.emplace_back(i, 0, 0, x, y);
  }
  sort(all_(vl));
  data_t min_angle = vl.front().l.r.arg() - vl.back().l.r.arg() + 2 * PI;
  int ansl = vl.back().id, ansr = vl.front().id;
  for (auto it = vl.begin() + 1; it != vl.end(); ++it) {
    auto now_angle = it->l.r.arg() - (it - 1)->l.r.arg();
    if (is_less(now_angle, min_angle)) {
      min_angle = now_angle;
      ansl = it->id;
      ansr = (it - 1)->id;
    }
  }
  cout << ansl << ' ' << ansr;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
