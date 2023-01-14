#include <bits/stdc++.h>
using namespace std;
using i32 = std::int32_t;
#define OPERATOR_OVERRIED_PAIR_(oper)                                       \
  template <typename Tp, typename Up>                                       \
  constexpr std::pair<Tp, Up> &operator oper##=(                            \
    std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) {                 \
    lhs.first oper## = rhs.first;                                           \
    lhs.second oper## = rhs.second;                                         \
    return lhs;                                                             \
  }                                                                         \
  template <typename Tp, typename Up>                                       \
  constexpr std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs,          \
                                            const std::pair<Tp, Up> &rhs) { \
    return lhs oper## = rhs;                                                \
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
using vi = vc<int>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define foreach_ref_(i, container) for (auto &i : (container))
#define all_(a) (a).begin(), (a).end()
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
#define read_container_(type, name, size) \
  type name(size);                        \
  foreach_ref_(i, name) std::cin >> i;
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
const i32 INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
namespace geometry2d {
using data_t = double;
using uint_data_t = uint64_t;
using int_data_t = std::make_signed<uint_data_t>::type;
template <typename Tp>
using cont_t = std::vector<Tp>;
template <typename Tp>
using cont_set_t = std::set<Tp>;
constexpr data_t EPS = 1e-8;
const data_t PI = std::acos(data_t{-1});
constexpr data_t DATA_MAX = std::numeric_limits<data_t>::max();
constexpr uint_data_t f2uint(data_t x) { return uint_data_t{x + EPS}; }
uint_data_t gcd(uint_data_t m, uint_data_t n) {
  return n == 0 ? m : gcd(n, m % n);
}
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
constexpr ptrdiff_t comp_rerr(data_t lhs, data_t rhs) {
  return sign((lhs - rhs) / std::abs(lhs));
}
constexpr bool is_less_rerr(data_t lhs, data_t rhs) {
  return is_negative((lhs - rhs) / std::abs(lhs));
}
constexpr bool is_equal_rerr(data_t lhs, data_t rhs) {
  return is_zero((lhs - rhs) / std::abs(lhs));
}
constexpr bool is_greater_rerr(data_t lhs, data_t rhs) {
  return is_positive((lhs - rhs) / std::abs(lhs));
}
constexpr bool is_intersect(data_t l1, data_t r1, data_t l2, data_t r2) {
  if (l1 > r1) std::swap(l1, r1);
  if (l2 > r2) std::swap(l2, r2);
  return !(is_less(r1, l2) || is_less(r2, l1));
}
constexpr bool is_in_middle(data_t l, data_t mid, data_t r) {
  return is_equal(l, mid) || is_equal(r, mid) || ((l < mid) ^ (r < mid));
}
struct Point2 {
  data_t x, y;
  constexpr Point2(data_t x = data_t{}, data_t y = data_t{}): x(x), y(y) {}
  friend std::istream &operator>>(std::istream &is, Point2 &rhs) {
    return is >> rhs.x >> rhs.y;
  }
  friend std::ostream &operator<<(std::ostream &os, const Point2 &rhs) {
    return os << rhs.x << ' ' << rhs.y;
  }
  constexpr Point2 &set_as_polar(data_t r, data_t theta) {
    return *this = {r * cos(theta), r * sin(theta)};
  }
  friend constexpr Point2
  lerp(const Point2 &lhs, const Point2 &rhs, data_t coord) {
    return lhs * coord + rhs * (1 - coord);
  }
  friend constexpr Point2 mid_point(const Point2 &lhs, const Point2 &rhs) {
    return lerp(lhs, rhs, 0.5);
  }
#define SCALA_OP(op)                             \
  constexpr Point2 &operator op##=(data_t n) {   \
    this->x op## = n;                            \
    this->y op## = n;                            \
    return *this;                                \
  }                                              \
  constexpr Point2 operator op(data_t n) const { \
    return Point2(*this) op## = n;               \
  }
  SCALA_OP(+)
  SCALA_OP(-)
  SCALA_OP(*)
  SCALA_OP(/)
#undef SCALA_OP
#define VEC_OP(op)                                        \
  constexpr Point2 &operator op##=(const Point2 & rhs) {  \
    this->x op## = rhs.x;                                 \
    this->y op## = rhs.y;                                 \
    return *this;                                         \
  }                                                       \
  constexpr Point2 operator op(const Point2 &rhs) const { \
    return Point2(*this) op## = rhs;                      \
  }
  VEC_OP(+)
  VEC_OP(-)
#undef VEC_OP
  constexpr Point2 operator-() const { return Point2{-x, -y}; }
  constexpr bool operator<(const Point2 &rhs) const {
    auto c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  constexpr bool operator==(const Point2 &rhs) const {
    return is_equal(x, rhs.x) && is_equal(y, rhs.y);
  }
  constexpr bool operator!=(const Point2 &rhs) const { return !(*this == rhs); }
  friend constexpr data_t dot_mul(const Point2 &lhs, const Point2 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend constexpr data_t cross_mul(const Point2 &lhs, const Point2 &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
#define SCALA_FUNC(name, func_body)      \
  constexpr auto name() const func_body; \
  friend constexpr auto name(const Point2 &lhs) { return lhs.name(); }
  SCALA_FUNC(arg, { return atan2(y, x); })
  SCALA_FUNC(arg2pi, {
    data_t tmp_ = arg();
    return is_negative(tmp_) ? tmp_ + 2 * PI : tmp_;
  })
  SCALA_FUNC(norm, { return x * x + y * y; })
  SCALA_FUNC(abs, { return sqrt(norm()); })
  static constexpr int QUAD__[9] = {5, 6, 7, 4, 0, 0, 3, 2, 1};
  SCALA_FUNC(quad, { return QUAD__[(sign(y) + 1) * 3 + sign(x) + 1]; })
#undef SCALA_FUNC
#define SELF_FUNC(name, func_body)         \
  constexpr Point2 &do_##name() func_body; \
  friend constexpr Point2 name(Point2 lhs) { return lhs.do_##name(); }
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
  constexpr Point2 &do_rot(data_t theta) {
    data_t _x = x, _y = y;
    x = _x * cos(theta) - _y * sin(theta);
    y = _x * sin(theta) + _y * cos(theta);
    return *this;
  };
  friend constexpr Point2 rot(Point2 lhs, data_t theta) {
    return lhs.do_rot(theta);
  }
};
constexpr data_t dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return std::hypot(lhs.x - rhs.x, lhs.y - rhs.y);
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
constexpr data_t dot(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y);
}
constexpr ptrdiff_t
dot_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return sign(dot(p1, p2, p3));
}
constexpr bool is_in_middle(Point2 a, Point2 m, Point2 b) {
  return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y);
}
constexpr data_t ang_PP(const Point2 &p1, const Point2 &p2) {
  return atan2(cross_mul(p1, p2), dot_mul(p1, p2));
}
constexpr data_t ang2pi_PP(const Point2 &p1, const Point2 &p2) {
  data_t res = ang_PP(p1, p2);
  return is_negative(res) ? res + 2 * PI : res;
}
struct Line2 {
  Point2 l, r;
  Line2() = default;
  constexpr Line2(const Point2 &start_, const Point2 &end_)
    : l(start_), r(end_) {}
  constexpr Line2(const data_t &start_x,
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
  constexpr friend bool operator<(const Line2 &lhs, const Line2 &rhs) {
    if (is_same_dir(lhs, rhs)) return rhs.is_include(lhs.l);
    auto vl = lhs.direction();
    auto vr = rhs.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_positive(cross_mul(vl, vr));
  }
  friend bool operator==(const Line2 &lhs, const Line2 &rhs) {
    return lhs.l == rhs.l && lhs.r == rhs.r;
  }
  constexpr data_t slope() const { return (r.y - l.y) / (r.x - l.x); }
  constexpr data_t slope_inv() const { return (r.x - l.x) / (r.y - l.y); }
  constexpr data_t intercept_v() const { return r.y - r.x * slope(); }
  constexpr data_t intercept_h() const { return r.x - r.y * slope_inv(); }
  constexpr data_t lerp_y(data_t x) const { return l.y + (x - l.x) * slope(); }
  constexpr data_t lerp_x(data_t y) const {
    return l.x + (y - l.y) * slope_inv();
  }
  friend constexpr bool is_parallel(const Line2 &lhs, const Line2 &rhs) {
    return is_zero(cross_mul(lhs.direction(), rhs.direction()));
  }
  friend constexpr bool is_same_dir(const Line2 &lhs, const Line2 &rhs) {
    return is_parallel(lhs, rhs) &&
           is_positive(dot_mul(lhs.direction(), rhs.direction()));
  }
  constexpr Point2 direction() const { return r - l; }
  constexpr bool is_include(const Point2 &p) const {
    return is_positive(cross(l, r, p));
  }
  constexpr bool passes_through(const Point2 &p) const {
    return is_zero(cross(l, r, p));
  }
  constexpr Line2 &do_push(data_t dist) {
    Point2 delta = direction().do_rot90().do_unit();
    delta *= dist;
    l += delta;
    r += delta;
    return *this;
  }
  friend constexpr Line2 push(Line2 line, data_t dist) {
    return line.do_push(dist);
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
constexpr bool
is_on_same_L(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return is_zero(cross(p1, p2, p3));
}
constexpr bool is_on_S(const Line2 &s1, const Point2 &p) {
  return is_on_same_L(s1.l, s1.r, p) && is_in_middle(s1.l, p, s1.r);
}
constexpr bool is_on_S_strict(const Line2 &s1, const Point2 &p) {
  return cross_sign(s1.l, s1.r, p) == 0 &&
         sign(dot_mul(p - s1.l, s1.l - s1.r)) *
             sign(dot_mul(p - s1.r, s1.l - s1.r)) <
           0;
}
constexpr data_t dist_PL(const Point2 &p, const Line2 &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  return dist_PP(p, proj(s1, p));
}
constexpr data_t dist_PS(const Point2 &p, const Line2 &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  Point2 h = proj(s1, p);
  if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
  return std::min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}
constexpr data_t dist_SS(const Line2 &s1, const Line2 &s2) {
  if (is_ins_SS(s1, s2)) return 0;
  return std::min({dist_PS(s1.l, s2),
                   dist_PS(s1.r, s2),
                   dist_PS(s2.l, s1),
                   dist_PS(s2.r, s1)});
}
struct Triangle {
  Point2 A, B, C;
  Triangle() = default;
  constexpr Triangle(const Point2 &a, const Point2 &b, const Point2 &c)
    : A(a), B(b), C(c) {}
  constexpr Triangle(const data_t &a_x,
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
  constexpr data_t area() const { return std::abs(cross(A, B, C)) / 2; }
  constexpr Point2 average_w(data_t wA, data_t wB, data_t wC) const {
    return (A * wA + B * wB + C * wC) / (wA + wB + wC);
  }
  constexpr bool is_acute() const {
    return is_positive(dot(A, B, C)) && is_positive(dot(B, C, A)) &&
           is_positive(dot(C, A, B));
  }
  constexpr bool is_right() const {
    return is_zero(dot(A, B, C)) || is_zero(dot(B, C, A)) ||
           is_zero(dot(C, A, B));
  }
  constexpr bool is_obtuse() const {
    return is_negative(dot(A, B, C)) || is_negative(dot(B, C, A)) ||
           is_negative(dot(C, A, B));
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
  constexpr Point2 center_G() const { return average_w(1, 1, 1); }
  constexpr Point2 center_O() const {
    Point2 p1 = mid_point(B, C), p2 = mid_point(C, A);
    return ins_LL({p1, p1 + (B - C).do_rot90()}, {p2, p2 + (C - A).do_rot90()});
  }
  constexpr Point2 center_H() const {
    return ins_LL({A, A + (B - C).do_rot90()}, {B, B + (C - A).do_rot90()});
  }
  constexpr Point2 center_N() const {
    return mid_point(center_O(), center_H());
  }
  Point2 center_X() const {
    data_t s3 = sqrt(data_t{3}), r = radius_I(), R = radius_O(),
           s = ((A - B).abs() + (B - C).abs() + (C - A).abs()) / 2;
    return center_I() * (s3 * (r * r + 2 * r * R + s * s)) +
           center_O() * (-6 * r * (s3 * R - 2 * s)) +
           center_G() * (-2 * r * (s3 * r + 3 * s));
  }
};
constexpr data_t area_T_abc(data_t a, data_t b, data_t c) {
  return std::sqrt((a + (b + c)) * (c - (a - b)) * (c + (a - b)) *
                   (a + (b - c))) /
         4;
}
struct Circle2 {
  Point2 o;
  data_t r;
  Circle2() = default;
  constexpr Circle2(const Point2 &c, data_t r): o(c), r(r) {}
  constexpr Circle2(const data_t &c_x, const data_t &c_y, data_t r_)
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
  constexpr data_t area(data_t angle = PI * 2) const {
    return angle * r * r / 2;
  }
  constexpr data_t crown_area(data_t angle = PI * 2) const {
    return (angle - std::sin(angle)) * r * r / 2;
  }
  constexpr data_t arc(data_t angle = PI * 2) const { return angle * r; }
  static const size_t lying_out = 4;
  static const size_t touch_ex = 3;
  static const size_t intersect_2p = 2;
  static const size_t touch_in = 1;
  static const size_t lying_in = 0;
  constexpr size_t relation_C(const Circle2 &c2) const {
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
  constexpr size_t relation_P(const Point2 &p) const {
    data_t d = dist_PP(o, p);
    if (is_less(d, r)) return inside;
    if (is_equal(d, r)) return on_border;
    return outside;
  }
  static const size_t intersect = 2;
  static const size_t tagante = 1;
  static const size_t otherwise = 0;
  constexpr size_t relation_L(const Line2 &l) const {
    data_t d = dist_PL(o, l);
    if (is_less(d, r)) return intersect;
    if (is_equal(d, r)) return tagante;
    return outside;
  }
  constexpr size_t relation_S(const Line2 &s) const {
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
  data_t x = dot_mul(l1.l - c.o, l1.r - l1.l), y = l1.direction().norm(),
         d = std::max(x * x - y * ((l1.l - c.o).norm() - c.r * c.r), data_t{});
  Point2 m = l1.l - l1.direction() * (x / y),
         dr = l1.direction() * (sqrt(d) / y);
  return {m - dr, m + dr};
}
cont_t<Point2> ins_CC(const Circle2 &c1, const Circle2 &c2) {
  assert(!is_equal(c1.o.x, c2.o.x) || !is_equal(c1.o.y, c2.o.y) ||
         !is_equal(c1.r, c2.r));
  auto state = c1.relation_C(c2);
  if (state == Circle2::lying_in || state == Circle2::lying_out) return {};
  data_t d = std::min(dist_PP(c1.o, c2.o), c1.r + c2.r);
  data_t y = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d),
         x = sqrt(c1.r * c1.r - y * y);
  Point2 dr = (c2.o - c1.o).do_unit();
  Point2 q1 = c1.o + dr * y, q2 = dr.do_rot90() * x;
  return {q1 - q2, q1 + q2};
}
constexpr Circle2
make_C_PPP(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  Point2 o = Triangle{p1, p2, p3}.center_O();
  return {o, dist_PP(o, p1)};
}
cont_t<Circle2> make_C_rPP(data_t r, const Point2 &p1, const Point2 &p2) {
  cont_t<Point2> ps = ins_CC({p1, r}, {p2, r});
  cont_t<Circle2> ret;
  for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
  return ret;
}
cont_t<Circle2> make_C_rPL(data_t r, const Point2 &p, const Line2 &l) {
  data_t dis = dist_PL(p, l);
  if (is_positive(dis - r * 2)) return {};
  Point2 dir = l.direction();
  dir *= r / dir.abs();
  Point2 dirl = rot90(dir), dirr = rot270(dir);
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
  Point2 dirl1 = rot90(dir1), dirr1 = rot270(dir1), dirl2 = rot90(dir2),
         dirr2 = rot270(dir2);
  Line2 u1 = Line2{l1.l + dirl1, l1.r + dirl1};
  Line2 u2 = Line2{l1.l + dirr1, l1.r + dirr1};
  Line2 v1 = Line2{l2.l + dirl2, l2.r + dirl2};
  Line2 v2 = Line2{l2.l + dirr2, l2.r + dirr2};
  return {{ins_LL(u1, v1), r},
          {ins_LL(u1, v2), r},
          {ins_LL(u2, v1), r},
          {ins_LL(u2, v2), r}};
}
cont_t<Circle2> make_C_rCC_ex(data_t r, const Circle2 &c1, const Circle2 &c2) {
  if (c1.relation_C(c2) == Circle2::inside) return {};
  cont_t<Point2> ps = ins_CC({c1.o, c1.r + r}, {c2.o, c2.r + r});
  cont_t<Circle2> ret;
  for (size_t i = 0; i < ps.size(); ++i) ret.emplace_back(ps[i], r);
  return ret;
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
  Point2 v = (p - c.o).do_rot90();
  return {inv_P(c, p + v), inv_P(c, p - v)};
}
constexpr Circle2 inv_L(const Circle2 &c, const Line2 &l) {
  Point2 p1 = inv_P(c, l.l), p2 = inv_P(c, l.r);
  return make_C_PPP(p1, p2, c.o);
}
cont_t<Point2> tan_CP(const Circle2 &c, const Point2 &p) {
  Point2 v = p - c.o;
  data_t x = v.norm(), d = x - c.r * c.r;
  if (is_negative(d)) return {};
  Point2 q1 = c.o + v * (c.r * c.r / x);
  Point2 q2 = v.do_rot90() * (c.r * sqrt(d) / x);
  return {q1 - q2, q1 + q2};
}
cont_t<Line2> extan_CC(const Circle2 &c1, const Circle2 &c2) {
  if (is_equal(c1.o.x, c2.o.x) && is_equal(c1.o.y, c2.o.y)) return {};
  cont_t<Line2> ret;
  if (is_equal(c1.r, c2.r)) {
    Point2 dr = (c2.o - c1.o).do_unit().do_rot90() * c1.r;
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
  if (is_equal(c1.o.x, c2.o.x) && is_equal(c1.o.y, c2.o.y)) return {};
  cont_t<Line2> ret;
  Point2 p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
  cont_t<Point2> ps = tan_CP(c1, p), qs = tan_CP(c2, p);
  for (size_t i = 0; i < std::min(ps.size(), qs.size()); ++i)
    ret.emplace_back(ps[i], qs[i]);
  return ret;
}
data_t sarea_CT(const Circle2 &c, const Point2 &p1, const Point2 &p2) {
  if (is_zero(cross(c.o, p1, p2))) return data_t{};
  cont_t<Point2> is = ins_CL(c, {p1, p2});
  if (is.empty()) return c.area(ang_PP(p1 - c.o, p2 - c.o));
  bool b1 = is_greater(dist_PP(p1, c.o), c.r),
       b2 = is_greater(dist_PP(p2, c.o), c.r);
  if (b1 && b2) {
    data_t res = c.area(ang_PP(p1 - c.o, p2 - c.o));
    if (!is_positive(dot(is[0], p1, p2)))
      res -= c.crown_area(ang_PP(is[0] - c.o, is[1] - c.o));
    return res;
  }
  if (b1)
    return c.area(ang_PP(p1 - c.o, is[0] - c.o)) + cross(c.o, is[0], p2) / 2;
  if (b2)
    return c.area(ang_PP(is[1] - c.o, p2 - c.o)) + cross(c.o, p1, is[1]) / 2;
  return cross(c.o, p1, p2) / 2;
}
constexpr data_t area_CC(const Circle2 &lhs, const Circle2 &rhs) {
  auto relation = lhs.relation_C(rhs);
  if (relation == Circle2::lying_out || relation == Circle2::touch_ex)
    return data_t{};
  if (relation == Circle2::lying_in || relation == Circle2::touch_in)
    return std::min(lhs.area(), rhs.area());
  data_t d = dist_PP(lhs.o, rhs.o);
  return lhs.crown_area(std::acos((lhs.r * lhs.r + d * d - rhs.r * rhs.r) /
                                  (2 * lhs.r * d)) *
                        2) +
         rhs.crown_area(std::acos((rhs.r * rhs.r + d * d - lhs.r * lhs.r) /
                                  (2 * rhs.r * d)) *
                        2);
}
data_t min_dist_Ps(const cont_t<Point2> &vp, ptrdiff_t l, ptrdiff_t r) {
  data_t ret = DATA_MAX;
  if (r - l <= 5) {
    for (ptrdiff_t i = l; i < r; ++i)
      for (ptrdiff_t j = l; j < i; ++j)
        ret = std::min(ret, dist_PP(vp[i], vp[j]));
    return ret;
  }
  ptrdiff_t mid = r - (r - l) / 2;
  ret = std::min(min_dist_Ps(vp, l, mid), min_dist_Ps(vp, mid, r));
  cont_t<Point2> q;
  for (ptrdiff_t i = l; i < r; ++i)
    if (std::abs(vp[i].x - vp[mid].x) <= ret) q.push_back(vp[i]);
  std::stable_sort(
    q.begin(), q.end(), [](const Point2 &lhs, const Point2 &rhs) -> bool {
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
    if (ret.relation_P(vp[i]) != Circle2::outside) continue;
    ret = Circle2{vp[i], 0};
    for (size_t j = 0; j < i; ++j) {
      if (ret.relation_P(vp[j]) != Circle2::outside) continue;
      ret = Circle2{mid_point(vp[i], vp[j]), dist_PP(vp[i], vp[j]) / 2};
      for (size_t k = 0; k < j; ++k) {
        if (ret.relation_P(vp[k]) != Circle2::outside) continue;
        ret = make_C_PPP(vp[i], vp[j], vp[k]);
      }
    }
  }
  return ret;
}
uint_data_t max_cover_Ps(const cont_t<Point2> &vp, const data_t r) {
  if (is_negative(r)) return uint_data_t{0};
  if (is_zero(r)) return uint_data_t{1};
  const data_t diam = r * 2;
  uint_data_t ans = 1;
  cont_t<std::pair<data_t, int_data_t>> angles;
  data_t dist;
  for (size_t i = 0; i < vp.size(); ++i) {
    angles.clear();
    for (size_t j = 0; j < vp.size(); ++j) {
      if (i == j || is_greater(dist = dist_PP(vp[i], vp[j]), diam)) continue;
      data_t delta = std::acos(dist / diam), polar = ang2pi_PP(vp[i], vp[j]);
      angles.emplace_back(polar - delta, 1);
      angles.emplace_back(polar + delta, -1);
    }
    std::sort(angles.begin(), angles.end());
    uint_data_t sum = 0;
    for (size_t j = 0; i < angles.size(); ++j)
      ans = std::max(ans, sum += angles[i].second);
  }
  return ans;
}
struct Polynomial2 {
  cont_t<Point2> vs;
  Polynomial2() = default;
  explicit Polynomial2(size_t size_): vs(size_) {}
  explicit Polynomial2(const cont_t<Point2> &vs_): vs(vs_) {}
  friend std::istream &operator>>(std::istream &is, Polynomial2 &rhs) {
    for (auto &i : rhs.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Polynomial2 &rhs) {
    for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it)
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
  cont_t<Point2>::const_iterator prev(cont_t<Point2>::const_iterator it) const {
    return --(it == vs.begin() ? it = vs.end() : it);
  }
  cont_t<Point2>::const_iterator next(cont_t<Point2>::const_iterator it) const {
    return ++it == vs.end() ? vs.begin() : it;
  }
  size_t prev(size_t idx) const { return idx == 0 ? vs.size() - 1 : idx - 1; }
  size_t next(size_t idx) const { return idx + 1 == vs.size() ? 0 : idx + 1; }
#define SCALA_FUNC(name, func_body) \
  auto name() const func_body;      \
  friend auto name(const Polynomial2 &lhs) { return lhs.name(); }
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
    for (auto &&now : vs)
      if (now == p) return onendpoint;
    bool result = false;
    for (size_t i = 0; i < vs.size(); ++i) {
      Point2 now_p = vs[i], next_p = vs[next(i)];
      if (is_on_S({now_p, next_p}, p)) return onborder;
      if (!is_greater(now_p.y, next_p.y)) std::swap(now_p, next_p);
      if (is_greater(p.y, now_p.y) || !is_greater(p.y, next_p.y)) continue;
      result ^= cross_sign(p, now_p, next_p) > 0;
    }
    return result ? inside : outside;
  }
  static const size_t covered = 2;
  static const size_t touch_in = 1;
  static const size_t otherwise = 0;
  size_t relation_C(const Circle2 &c) const {
    size_t x = covered;
    if (relation_P(c.o) != Circle2::inside) return otherwise;
    for (size_t i = 0; i < vs.size(); ++i) {
      size_t state = c.relation_S({vs[i], vs[next(i)]});
      if (state == Circle2::intersect) return otherwise;
      if (state == Circle2::tagante) x = touch_in;
    }
    return x;
  }
  void resort_in_clockwise() {
    std::sort(vs.begin(), vs.end(), [](const Point2 &lhs, const Point2 &rhs) {
      return lhs.quad() > rhs.quad();
    });
  }
  void resort_in_counterclockwise() {
    std::sort(vs.begin(), vs.end(), [](const Point2 &lhs, const Point2 &rhs) {
      return lhs.quad() < rhs.quad();
    });
  }
  bool is_convex() const {
    bool flag[2] = {false, false};
    size_t sz = vs.size();
    if (sz < 3) return true;
    for (size_t i = 0, j = next(i), k = next(j); i < sz;
         ++i, j = next(j), k = next(k)) {
      auto sgn = cross_sign(vs[i], vs[j], vs[k]);
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
    Point2 ret{};
    data_t area{};
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
data_t area_PolyC(const Polynomial2 &poly, const Circle2 &c) {
  data_t ans{};
  size_t sz = poly.vs.size();
  if (sz < 3) return ans;
  for (size_t i = 0; i < sz; ++i)
    ans += sarea_CT(c, poly[i], poly[poly.next(i)]);
  return std::abs(ans);
}
struct ConvexHull2: public Polynomial2 {
  ConvexHull2() = default;
  explicit ConvexHull2(size_t size_): Polynomial2(size_) {}
  explicit ConvexHull2(const cont_t<Point2> &vs_,
                       bool inited = false,
                       bool strict = true)
    : Polynomial2(vs_) {
    if (!inited) strict ? init() : init_nonstrict();
  }
  friend std::istream &operator>>(std::istream &is, ConvexHull2 &rhs) {
    for (auto &i : rhs.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const ConvexHull2 &rhs) {
    for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it)
      os << *it << ' ';
    return os << rhs.vs.back();
  }
  ConvexHull2 &init() {
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return *this;
    resort();
    cont_t<Point2> cvh(sz * 2);
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
    cont_t<Point2> cvh(sz * 2);
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
  size_t relation_P(const Point2 &p) const override {
    for (auto &&now : vs)
      if (now == p) return onendpoint;
    size_t sz = vs.size();
    for (size_t i = 0; i < sz; ++i)
      if (is_on_S({vs[i], vs[next(i)]}, p)) return onborder;
    if (sz < 3) return outside;
    if (is_positive(cross(vs.front(), p, vs[1])) ||
        is_positive(cross(vs.front(), vs.back(), p)))
      return outside;
    auto it =
      std::lower_bound(vs.begin() + 1,
                       vs.end(),
                       p,
                       [&](const Point2 &lhs, const Point2 &rhs) {
                         return is_positive(cross(vs.front(), lhs, rhs));
                       }) -
      1;
    auto next_it = next(it);
    auto res = cross_sign(p, *it, *next_it);
    if (res) return ~res ? inside : outside;
    return !res && !is_positive(dot(p, *it, *next_it)) ? inside : outside;
  }
  friend bool is_ins_cvh(const ConvexHull2 &cvhl, const ConvexHull2 &cvhr) {
    for (auto &&now : cvhl.vs)
      if (cvhr.relation_P(now)) return false;
    for (auto &&now : cvhr.vs)
      if (cvhl.relation_P(now)) return false;
    size_t n = cvhl.vs.size(), m = cvhr.vs.size();
    if (n > 1 && m > 1) {
      for (size_t l = 0, nextl = 1; l < n; nextl = cvhl.next(l = nextl))
        for (size_t r = 0, nextr = 1; r < m; nextr = cvhl.next(r = nextr))
          if (is_ins_SS({cvhl[l], cvhl[nextl]}, {cvhr[r], cvhr[nextr]}))
            return false;
    } else if (n == 1) {
      if (cvhl[0] == cvhr[0]) return false;
      if (m == 1) return true;
      return !is_on_S({cvhr[0], cvhr[1]}, cvhl[0]);
    } else {
      if (is_on_S({cvhl[0], cvhl[1]}, cvhr[0])) return false;
      if (m == 1) return true;
      return !is_ins_SS({cvhl[0], cvhl[1]}, {cvhr[0], cvhr[1]});
    }
    return true;
  }
  data_t diameter() const {
    size_t sz = vs.size();
    if (sz <= 1) return data_t{};
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
  friend Polynomial2 coverage_rect_with_min_area(ConvexHull2 &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[1], lhs[1]}};
    lhs.vs.push_back(lhs.vs[0]);
    data_t ans = DATA_MAX;
    size_t r = 1, p = 1, q;
    size_t ans_i, ans_r, ans_p, ans_q;
    for (size_t i = 0; i < sz; ++i) {
      while (!is_negative(cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r + 1]) -
                          cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r])))
        r = (r + 1) % sz;
      while (!is_negative(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p + 1]) -
                          dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p])))
        p = (p + 1) % sz;
      if (i == 0) q = p;
      while (!is_positive(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q + 1]) -
                          dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q])))
        q = (q + 1) % sz;
      data_t tmp = cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r]) *
                   (dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p]) -
                    dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q])) /
                   (lhs.vs[i] - lhs.vs[i + 1]).norm();
      if (ans > tmp) {
        ans = tmp;
        ans_i = i;
        ans_r = r;
        ans_p = p;
        ans_q = q;
      }
    }
    Point2 dir = Line2{lhs[ans_i], lhs[ans_i + 1]}.direction(),
           vdir = rot90(dir);
    Line2 li{lhs[ans_i], lhs[ans_i] + dir}, lp{lhs[ans_p], lhs[ans_p] + vdir},
      lr{lhs[ans_r], lhs[ans_r] + dir}, lq{lhs[ans_q], lhs[ans_q] + vdir};
    Polynomial2 ret{cont_t<Point2>{
      ins_LL(li, lp), ins_LL(lp, lr), ins_LL(lr, lq), ins_LL(lq, li)}};
    lhs.vs.pop_back();
    return ret;
  }
  friend Polynomial2 coverage_rect_with_min_circum(ConvexHull2 &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[1], lhs[1]}};
    lhs.vs.push_back(lhs.vs[0]);
    data_t ans = DATA_MAX;
    size_t r = 1, p = 1, q;
    size_t ans_i, ans_r, ans_p, ans_q;
    for (size_t i = 0; i < sz; ++i) {
      while (!is_negative(cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r + 1]) -
                          cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r])))
        r = (r + 1) % sz;
      while (!is_negative(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p + 1]) -
                          dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p])))
        p = (p + 1) % sz;
      if (i == 0) q = p;
      while (!is_positive(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q + 1]) -
                          dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q])))
        q = (q + 1) % sz;
      data_t tmp = (cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r]) +
                    (dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p]) -
                     dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q]))) /
                   (lhs.vs[i] - lhs.vs[i + 1]).abs();
      if (ans > tmp) {
        ans = tmp;
        ans_i = i;
        ans_r = r;
        ans_p = p;
        ans_q = q;
      }
    }
    Point2 dir = Line2{lhs[ans_i], lhs[ans_i + 1]}.direction(),
           vdir = rot90(dir);
    Line2 li{lhs[ans_i], lhs[ans_i] + dir}, lp{lhs[ans_p], lhs[ans_p] + vdir},
      lr{lhs[ans_r], lhs[ans_r] + dir}, lq{lhs[ans_q], lhs[ans_q] + vdir};
    Polynomial2 ret{cont_t<Point2>{
      ins_LL(li, lp), ins_LL(lp, lr), ins_LL(lr, lq), ins_LL(lq, li)}};
    lhs.vs.pop_back();
    return ret;
  }
  ConvexHull2 &do_minkowski_sum_nonstrict(const ConvexHull2 &rhs) {
    size_t n = vs.size(), m = rhs.vs.size();
    if (!m) return *this;
    if (!n) return *this = rhs;
    cont_t<Point2> result;
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
    cont_t<Point2> cvc;
    for (size_t i = 0; i < sz; ++i) {
      Point2 p1 = vs[i], p2 = vs[next(i)];
      ptrdiff_t d1 = cross_sign(l.l, l.r, p1), d2 = cross_sign(l.l, l.r, p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, l));
    }
    vs = cvc;
    return *this;
  }
  friend ConvexHull2 ins_CVHhP(ConvexHull2 poly, const Line2 &l) {
    return poly.do_ins_CVHhP(l);
  }
};
ConvexHull2 ins_hP(cont_t<Line2> vl) {
  auto check = [](const Line2 &u, const Line2 &v, const Line2 &w) -> bool {
    return w.is_include(ins_LL(u, v));
  };
  std::sort(vl.begin(), vl.end());
  vl.erase(std::unique(vl.begin(), vl.end()), vl.end());
  if (vl.size() < 3) return ConvexHull2();
  std::deque<Line2> q;
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
  return ConvexHull2{ret, true};
}
struct DynamicCVH2 {
  struct DynamicCVH2Base {
    ptrdiff_t sgn = 1;
    cont_set_t<Point2> vs;
    DynamicCVH2Base() = default;
    explicit DynamicCVH2Base(ptrdiff_t sgn = 1): sgn(sgn) {}
    bool contains(const Point2 &p) const {
      auto it = vs.lower_bound({p.x, -DATA_MAX});
      if (it == vs.end()) return false;
      if (it->x == p.x) return sign(p.y - it->y) * sgn <= 0;
      if (it == vs.begin()) return false;
      auto j = it;
      return cross_sign(*(--j), *it, p) * sgn <= 0;
    }
    bool erase(cont_set_t<Point2>::const_iterator it) {
      if (it == vs.begin()) return false;
      auto j = it, k = it;
      if (++k == vs.end()) return false;
      return cross_sign(*(--j), *it, *k) * sgn >= 0 ? vs.erase(it),
             true : false;
    }
    DynamicCVH2Base &insert(const Point2 &p) {
      if (contains(p)) return *this;
      auto tmp = vs.lower_bound({p.x, -DATA_MAX});
      if (tmp != vs.end() && tmp->x == p.x) vs.erase(tmp);
      vs.insert(p);
      auto i = vs.find(p), j = i;
      if (i != vs.begin()) {
        --j;
        while (erase(j++)) --j;
      }
      if (++j != vs.end())
        while (erase(j--)) ++j;
      return *this;
    }
  };
  DynamicCVH2Base hcvh_up{1}, hcvh_down{-1};
  DynamicCVH2() = default;
  bool contains(const Point2 &p) const {
    return hcvh_up.contains(p) && hcvh_down.contains(p);
  }
  DynamicCVH2 &insert(const Point2 &p) {
    hcvh_up.insert(p);
    hcvh_down.insert(p);
    return *this;
  }
  ConvexHull2 to_CVH() const {
    ConvexHull2 ret;
    for (auto it = hcvh_up.vs.begin(); it != hcvh_up.vs.end(); ++it)
      ret.vs.push_back(*it);
    for (auto it = hcvh_down.vs.begin(); it != hcvh_down.vs.end(); ++it)
      ret.vs.push_back(*it);
    ret.resort_in_counterclockwise();
    return ret;
  }
};
}  // namespace geometry2d
using namespace geometry2d;
struct Node {
  size_t idx_l, idx_r;
  Line2 line;
  Node(size_t idx_l, size_t idx_r, const Point2 &pl, const Point2 &pr)
    : idx_l(idx_l), idx_r(idx_r), line(pl, pr) {}
  friend bool operator<(const Node &lhs, const Node &rhs) {
    return lhs.line < rhs.line;
  }
};
auto solve([[maybe_unused]] int t_) -> void {
  read_var_(int, n);
  read_container_(vc<Point2>, vp, n);
  vc<Node> vl;
  for_(i, 0, n - 1)
    for_(j, 0, n - 1) {
      if (i == j) continue;
      vl.emplace_back(i, j, vp[i], vp[j]);
    }
  sort(all_(vl));
  vi f(n + 1);
  int ans = 0;
  for_(i, 0, n - 1) {
    fill(all_(f), -INF);
    f[i] = 0;
    for_(j, 0, vl.size() - 1) chkmax(f[vl[j].idx_r], f[vl[j].idx_l] + 1);
    chkmax(ans, f[i]);
  }
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
