#include <bits/stdc++.h>
using namespace std;
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
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
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
const double EPS = 1e-6;
const double PI = acos(-1.0);
namespace geometry2d {
using data_t = double;
using uint_data_t = uint64_t;
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
  void resort_in_clockwise() {
    std::sort(vs.begin(), vs.end(), [](const Point2 &lhs, const Point2 &rhs) {
      return lhs.quad() == rhs.quad() ? is_negative(cross_mul(lhs, rhs)) :
                                        lhs.quad() > rhs.quad();
    });
  }
  void resort_in_counterclockwise() {
    std::sort(vs.begin(), vs.end(), [](const Point2 &lhs, const Point2 &rhs) {
      return lhs.quad() == rhs.quad() ? is_positive(cross_mul(lhs, rhs)) :
                                        lhs.quad() < rhs.quad();
    });
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
    data_t ret = dist_PP(vs.back(), vs.front());
    for (size_t i = 0; i < vs.size() - 1; ++i) ret += dist_PP(vs[i], vs[i + 1]);
    return ret;
  })
  SCALA_FUNC(area, {
    data_t ret = cross_mul(vs.back(), vs.front());
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
    size_t is = 0, js = 0;
    for (size_t k = 1; k < sz; ++k) {
      is = vs[k] < vs[is] ? k : is;
      js = vs[js] < vs[k] ? k : js;
    }
    size_t i = is, j = js;
    data_t ret = dist_PP(vs[i], vs[j]);
    do {
      (++(cross_mul(vs[next(i)] - vs[i], vs[next(j)] - vs[j]) >= 0 ? j : i)) %=
        sz;
      ret = std::max(ret, dist_PP(vs[i], vs[j]));
    } while (i != is || j != js);
    return ret;
  }
  friend data_t max_dis_CVH(const ConvexHull2 &cvhl, const ConvexHull2 &cvhr) {
    size_t is = 0, js = 0;
    size_t szl = cvhl.vs.size(), szr = cvhr.vs.size();
    data_t ans = DATA_MAX;
    for (size_t i = 0; i < szl; ++i)
      if (cvhl[i].y < cvhl[is].y) is = i;
    for (size_t i = 0; i < szr; ++i)
      if (cvhr[i].y < cvhr[js].y) js = i;
    for (size_t i = 0; i < szl; ++i) {
      size_t state;
      while ((state = sign(cross_mul(cvhl[is] - cvhl[cvhl.next(is)],
                                     cvhr[js] - cvhr[cvhr.next(js)]))) < 0)
        js = cvhr.next(js);
      ans =
        std::min(ans,
                 state ? dist_PS(cvhr[js], {cvhl[is], cvhl[cvhl.next(is)]}) :
                         dist_SS({cvhl[is], cvhl[cvhl.next(is)]},
                                 {cvhr[js], cvhr[cvhr.next(js)]}));
      is = cvhl.next(is);
    }
    return ans;
  }
  friend Polynomial2 coverage_rect_with_min_area(const ConvexHull2 &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[1], lhs[1]}};
    data_t ans = DATA_MAX;
    size_t r = 1, p = 1, q = 1;
    size_t ans_i, ans_r, ans_p, ans_q;
    for (size_t i = 0; i < sz; ++i) {
      while (!is_negative(
        cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(r)]) -
        cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r])))
        r = lhs.next(r);
      while (
        !is_negative(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(p)]) -
                     dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p])))
        p = lhs.next(p);
      if (i == 0) q = p;
      while (
        !is_positive(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(q)]) -
                     dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q])))
        q = lhs.next(q);
      data_t tmp = cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r]) *
                   (dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p]) -
                    dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q])) /
                   (lhs.vs[i] - lhs.vs[lhs.next(i)]).norm();
      if (ans > tmp) {
        ans = tmp;
        ans_i = i;
        ans_r = r;
        ans_p = p;
        ans_q = q;
      }
    }
    Point2 dir = Line2{lhs[ans_i], lhs[lhs.next(ans_i)]}.direction(),
           vdir = rot90(dir);
    Line2 li{lhs[ans_i], lhs[ans_i] + dir}, lp{lhs[ans_p], lhs[ans_p] + vdir},
      lr{lhs[ans_r], lhs[ans_r] + dir}, lq{lhs[ans_q], lhs[ans_q] + vdir};
    Polynomial2 ret{cont_t<Point2>{
      ins_LL(li, lp), ins_LL(lp, lr), ins_LL(lr, lq), ins_LL(lq, li)}};
    return ret;
  }
  friend Polynomial2 coverage_rect_with_min_circum(const ConvexHull2 &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[1], lhs[1]}};
    data_t ans = DATA_MAX;
    size_t r = 1, p = 1, q = 1;
    size_t ans_i = 0, ans_r, ans_p, ans_q;
    for (size_t i = 0; i < sz; ++i) {
      while (!is_negative(
        cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(r)]) -
        cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r])))
        r = lhs.next(r);
      while (
        !is_negative(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(p)]) -
                     dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p])))
        p = lhs.next(p);
      if (i == 0) q = p;
      while (
        !is_positive(dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[lhs.next(q)]) -
                     dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q])))
        q = lhs.next(q);
      data_t tmp = (cross(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[r]) +
                    (dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[p]) -
                     dot(lhs.vs[i], lhs.vs[lhs.next(i)], lhs.vs[q]))) /
                   (lhs.vs[i] - lhs.vs[lhs.next(i)]).abs();
      if (ans > tmp) {
        ans = tmp;
        ans_i = i;
        ans_r = r;
        ans_p = p;
        ans_q = q;
      }
    }
    Point2 dir = Line2{lhs[ans_i], lhs[lhs.next(ans_i)]}.direction(),
           vdir = rot90(dir);
    Line2 li{lhs[ans_i], lhs[ans_i] + dir}, lp{lhs[ans_p], lhs[ans_p] + vdir},
      lr{lhs[ans_r], lhs[ans_r] + dir}, lq{lhs[ans_q], lhs[ans_q] + vdir};
    Polynomial2 ret{cont_t<Point2>{
      ins_LL(li, lp), ins_LL(lp, lr), ins_LL(lr, lq), ins_LL(lq, li)}};
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
auto solve([[maybe_unused]] int t_) -> void {
  read_var_(int, n);
  ConvexHull2 cvh(n);
  cin >> cvh;
  Polynomial2 rect = coverage_rect_with_min_area(cvh.init());
  cout << rect.area() << '\n';
  size_t start = 0;
  for_(i, 0, 3) {
    if (is_zero(rect[i].x)) rect[i].x = 0;
    if (is_zero(rect[i].y)) rect[i].y = 0;
  }
  for_(i, 0, 3)
    if (is_less(rect[i].y, rect[start].y) ||
        (is_equal(rect[i].y, rect[start].y) &&
         is_less(rect[i].x, rect[start].x)))
      start = i;
  for (size_t i = start; i < 4; ++i) cout << rect[i] << '\n';
  for (size_t i = 0; i < start; ++i) cout << rect[i] << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  cout << fixed << setprecision(5);
  solve(i_);
  return 0;
}
