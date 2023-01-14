#include <bits/stdc++.h>
struct CustomHash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
      std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
#define all_(a) (a).begin(), (a).end()
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
}
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
}
template <class Tp>
constexpr auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
#define TPL_SIZE_(Tuple) std::tuple_size_v<std::remove_reference_t<Tuple>>
namespace tuple_detail_ {
template <std::size_t Begin, class Tuple, std::size_t... Is>
constexpr auto subtuple_impl_(Tuple &&t, std::index_sequence<Is...>) {
  return std::make_tuple(std::get<Is + Begin>(t)...);
}
template <class Tuple, class BinOp, std::size_t... Is>
constexpr auto
apply2_impl_(BinOp &&f, Tuple &&lhs, Tuple &&rhs, std::index_sequence<Is...>) {
  return std::make_tuple(
    std::forward<BinOp>(f)(std::get<Is>(lhs), std::get<Is>(rhs))...);
}
}  // namespace tuple_detail_
template <std::size_t Begin, std::size_t Len, class Tuple>
constexpr auto subtuple(Tuple &&t) {
  static_assert(Begin <= TPL_SIZE_(Tuple) && Len <= TPL_SIZE_(Tuple) &&
                  Begin + Len <= TPL_SIZE_(Tuple),
                "Out of range");
  return tuple_detail_::subtuple_impl_<Begin>(t,
                                              std::make_index_sequence<Len>());
}
template <std::size_t Pos, class Tp, class Tuple>
constexpr auto tuple_push(Tp &&v, Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        std::make_tuple(v),
                        subtuple<Pos, TPL_SIZE_(Tuple) - Pos>(t));
}
template <class Tp, class Tuple>
constexpr auto tuple_push_front(Tp &&v, Tuple &&t) {
  return tuple_push<0>(v, t);
}
template <class Tp, class Tuple>
constexpr auto tuple_push_back(Tp &&v, Tuple &&t) {
  return tuple_push<TPL_SIZE_(Tuple)>(v, t);
}
template <std::size_t Pos, class Tuple>
constexpr auto tuple_pop(Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        subtuple<Pos + 1, TPL_SIZE_(Tuple) - Pos - 1>(t));
}
template <class Tuple>
constexpr auto tuple_pop_front(Tuple &&t) {
  return tuple_pop<0>(t);
}
template <class Tuple>
constexpr auto tuple_pop_back(Tuple &&t) {
  return tuple_pop<TPL_SIZE_(Tuple) - 1>(t);
}
template <class Tuple, class BinOp>
constexpr auto apply2(BinOp &&f, Tuple &&lhs, Tuple &&rhs) {
  return tuple_detail_::apply2_impl_(
    f, lhs, rhs, std::make_index_sequence<TPL_SIZE_(Tuple)>());
}
#define OO_PTEQ_(op)                                                          \
  template <class Tp, class Up>                                               \
  constexpr auto operator op(std::pair<Tp, Up> lhs,                           \
                             const std::pair<Tp, Up> &rhs) {                  \
    return {lhs.first op rhs.first, lhs.second op rhs.second};                \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op(std::tuple<Ts...> const &lhs,                    \
                             std::tuple<Ts...> const &rhs) {                  \
    return apply2([](auto &&l, auto &&r) { return l op r; }, lhs, rhs);       \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator op##=(std::pair<Tp, Up> &lhs,         \
                                              const std::pair<Tp, Up> &rhs) { \
    lhs.first op## = rhs.first;                                               \
    lhs.second op## = rhs.second;                                             \
    return lhs;                                                               \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op##=(std::tuple<Ts...> &lhs,                       \
                                const std::tuple<Ts...> &rhs) {               \
    return lhs = lhs op rhs;                                                  \
  }
OO_PTEQ_(+)
OO_PTEQ_(-)
OO_PTEQ_(*)
OO_PTEQ_(/)
OO_PTEQ_(%)
OO_PTEQ_(&)
OO_PTEQ_(|)
OO_PTEQ_(^)
OO_PTEQ_(<<)
OO_PTEQ_(>>)
#undef OO_PTEQ_
#undef TPL_SIZE_
template <class Tp, class Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <typename... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p);
  return is;
}
template <typename... Ts>
std::ostream &operator<<(std::ostream &os, const std::tuple<Ts...> &p) {
  std::apply(
    [&](Ts const &...targs) {
      std::size_t n{0};
      ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
    },
    p);
  return os;
}
template <class Ch,
          class Tr,
          class Ct,
          std::enable_if_t<std::is_same_v<decltype(std::declval<Ct>().begin()),
                                          typename Ct::iterator> &&
                           std::is_same_v<decltype(std::declval<Ct>().end()),
                                          typename Ct::iterator>> * = nullptr>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Ct &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
const double EPS = 1e-6;
const double PI = acos(-1.0);
using namespace std;
namespace geometry2d {
using data_t = double;
using uint_data_t = uint64_t;
template <typename Tp>
using cont_t = std::vector<Tp>;
constexpr data_t EPS = 1e-8;
#if __cplusplus >= 201703l
using std::gcd, std::lcm;
uint_data_t gcd(uint_data_t m, uint_data_t n) {
  return n == 0 ? m : gcd(n, m % n);
}
uint_data_t lcm(uint_data_t m, uint_data_t n) { return m / gcd(m, n) * n; }
#define DIFF__(x, y) ((x) - (y))
constexpr ptrdiff_t sgn(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
constexpr bool is_negative(data_t x) { return sgn(x) & 2; }
constexpr bool is_zero(data_t x) { return !sgn(x); }
constexpr bool is_positive(data_t x) { return (sgn(x) + 1) & 2; }
constexpr ptrdiff_t comp(data_t lhs, data_t rhs) {
  return sgn(DIFF__(lhs, rhs));
}
constexpr bool is_less(data_t lhs, data_t rhs) {
  return is_negative(DIFF__(lhs, rhs));
}
constexpr bool is_equal(data_t lhs, data_t rhs) {
  return is_zero(DIFF__(lhs, rhs));
}
constexpr bool is_greater(data_t lhs, data_t rhs) {
  return is_positive(DIFF__(lhs, rhs));
}
#undef DIFF__
const data_t PI = std::acos(data_t{-1});
constexpr uint_data_t f2uint(data_t x) { return uint_data_t{x + EPS}; }
constexpr bool is_intersect(data_t l1, data_t r1, data_t l2, data_t r2) {
  if (l1 > r1) std::swap(l1, r1);
  if (l2 > r2) std::swap(l2, r2);
  return !(is_less(r1, l2) || is_less(r2, l1));
}
constexpr bool is_in_middle(data_t l, data_t mid, data_t r) {
  return is_equal(l, mid) || is_equal(r, mid) || ((l < mid) ^ (r < mid));
}
#define FUNC_SCALA0(self, name, ...)       \
  constexpr auto name() const __VA_ARGS__; \
  friend constexpr auto name(const self &lhs) { return lhs.name(); }
#define FUNC_iSCALA0(self, name, ...) \
  auto name() const __VA_ARGS__;      \
  friend auto name(const self &lhs) { return lhs.name(); }
#define FUNC_SCALA1(self, name, rhs_type1, rhs1, ...)           \
  constexpr auto name(rhs_type1 rhs1) const __VA_ARGS__;        \
  friend constexpr auto name(const self &lhs, rhs_type1 rhs1) { \
    return lhs.name(rhs1);                                      \
  }
#define FUNC_SELF0(self, name, ...)        \
  constexpr self &do_##name() __VA_ARGS__; \
  friend constexpr self name(self lhs) { return lhs.do_##name(); }
#define FNUC_SELF1(self, name, rhs_type1, rhs1, ...)     \
  constexpr self &do_##name(rhs_type1 rhs1) __VA_ARGS__; \
  friend constexpr self name(self lhs, rhs_type1 rhs1) { \
    return lhs.do_##name(rhs1);                          \
  }
#define FNUC_iSELF1(self, name, rhs_type1, rhs1, ...) \
  self &do_##name(rhs_type1 rhs1) __VA_ARGS__;        \
  friend self name(self lhs, rhs_type1 rhs1) { return lhs.do_##name(rhs1); }
enum RELA_PoP { outside_pop, onborder_pop, onendpoint_pop, inside_pop };
struct Point {
  data_t x, y;
  constexpr Point(data_t x = data_t{}, data_t y = data_t{}): x(x), y(y) {}
  friend std::istream &operator>>(std::istream &is, Point &rhs) {
    return is >> rhs.x >> rhs.y;
  }
  friend std::ostream &operator<<(std::ostream &os, const Point &rhs) {
    return os << rhs.x << ' ' << rhs.y;
  }
  constexpr Point &set_as_polar(data_t r, data_t theta) {
    return *this = {r * std::cos(theta), r * std::sin(theta)};
  }
  friend constexpr Point
  lerp(const Point &lhs, const Point &rhs, data_t coord) {
    return lhs * coord + rhs * (1 - coord);
  }
  friend constexpr Point mid_point(const Point &lhs, const Point &rhs) {
    return lerp(lhs, rhs, 0.5);
  }
#define SCALA_OP(op)                          \
  constexpr Point &operator op##=(data_t n) { \
    this->x op## = n;                         \
    this->y op## = n;                         \
    return *this;                             \
  }                                           \
  constexpr Point operator op(data_t n) const { return Point(*this) op## = n; }
  SCALA_OP(+)
  SCALA_OP(-)
  SCALA_OP(*)
  SCALA_OP(/)
#undef SCALA_OP
#define VEC_OP(op)                                      \
  constexpr Point &operator op##=(const Point & rhs) {  \
    this->x op## = rhs.x;                               \
    this->y op## = rhs.y;                               \
    return *this;                                       \
  }                                                     \
  constexpr Point operator op(const Point &rhs) const { \
    return Point(*this) op## = rhs;                     \
  }
  VEC_OP(+)
  VEC_OP(-)
#undef VEC_OP
  constexpr Point operator-() const { return Point{-x, -y}; }
  constexpr bool operator<(const Point &rhs) const {
    auto c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  constexpr bool operator==(const Point &rhs) const {
    return is_equal(x, rhs.x) && is_equal(y, rhs.y);
  }
  constexpr bool operator!=(const Point &rhs) const { return !(*this == rhs); }
  friend constexpr data_t operator*(const Point &lhs, const Point &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend constexpr data_t operator^(const Point &lhs, const Point &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
  friend constexpr data_t dot_mul(const Point &lhs, const Point &rhs) {
    return lhs * rhs;
  }
  friend constexpr data_t cross_mul(const Point &lhs, const Point &rhs) {
    return lhs ^ rhs;
  }
  FUNC_SCALA0(Point, arg, { return std::atan2(y, x); })
  FUNC_SCALA0(Point, arg2pi, {
    data_t tmp_ = arg();
    return is_negative(tmp_) ? tmp_ + 2 * PI : tmp_;
  })
  FUNC_SCALA0(Point, norm, { return x * x + y * y; })
  FUNC_SCALA0(Point, abs, { return sqrt(norm()); })
  static constexpr int QUAD__[9] = {5, 6, 7, 4, 0, 0, 3, 2, 1};
  FUNC_SCALA0(Point, quad, { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; })
  FUNC_SELF0(Point, rot90, {
    data_t tmp = x;
    x = -y;
    y = tmp;
    return *this;
  })
  FUNC_SELF0(Point, rot180, {
    x = -x;
    y = -y;
    return *this;
  })
  FUNC_SELF0(Point, rot270, {
    data_t tmp = y;
    y = -x;
    x = tmp;
    return *this;
  })
  FUNC_SELF0(Point, unit, { return *this /= abs(); })
  FNUC_SELF1(Point, rot, data_t, theta, {
    data_t _x = x, _y = y;
    x = _x * std::cos(theta) - _y * std::sin(theta);
    y = _x * std::sin(theta) + _y * std::cos(theta);
    return *this;
  })
};
constexpr Point make_P_polar(data_t r, data_t theta) {
  return Point{r * std::cos(theta), r * std::sin(theta)};
}
constexpr data_t dist_PP(const Point &lhs, const Point &rhs) {
  return std::hypot(lhs.x - rhs.x, lhs.y - rhs.y);
}
constexpr data_t dist_MaPP(const Point &lhs, const Point &rhs) {
  return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y);
}
constexpr data_t dist_ChPP(const Point &lhs, const Point &rhs) {
  return std::max(std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y));
}
constexpr data_t cross(const Point &p1, const Point &p2, const Point &p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}
constexpr ptrdiff_t
sgn_cross(const Point &p1, const Point &p2, const Point &p3) {
  return sgn(cross(p1, p2, p3));
}
constexpr data_t dot(const Point &p1, const Point &p2, const Point &p3) {
  return (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y);
}
constexpr ptrdiff_t sgn_dot(const Point &p1, const Point &p2, const Point &p3) {
  return sgn(dot(p1, p2, p3));
}
constexpr bool is_in_middle(Point a, Point m, Point b) {
  return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y);
}
constexpr data_t ang_PP(const Point &p1, const Point &p2) {
  return std::atan2(cross_mul(p1, p2), dot_mul(p1, p2));
}
constexpr data_t ang2pi_PP(const Point &p1, const Point &p2) {
  data_t res = ang_PP(p1, p2);
  return is_negative(res) ? res + 2 * PI : res;
}
struct Line {
  Point l, r;
  Line() = default;
  constexpr Line(const Point &start_, const Point &end_): l(start_), r(end_) {}
  constexpr Line(const data_t &start_x,
                 const data_t &start_y,
                 const data_t &end_x,
                 const data_t &end_y)
    : l(start_x, start_y), r(end_x, end_y) {}
  friend std::istream &operator>>(std::istream &is, Line &rhs) {
    return is >> rhs.l >> rhs.r;
  }
  friend std::ostream &operator<<(std::ostream &os, const Line &rhs) {
    return os << rhs.l << ' ' << rhs.r;
  }
  constexpr friend bool operator<(const Line &lhs, const Line &rhs) {
    if (is_same_dir(lhs, rhs)) return rhs.is_include_strict(lhs.l);
    auto vl = lhs.direction();
    auto vr = rhs.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_positive(cross_mul(vl, vr));
  }
  friend bool operator==(const Line &lhs, const Line &rhs) {
    return lhs.l == rhs.l && lhs.r == rhs.r;
  }
  FUNC_SCALA0(Line, slope, { return (r.y - l.y) / (r.x - l.x); })
  FUNC_SCALA0(Line, slope_inv, { return (r.x - l.x) / (r.y - l.y); })
  FUNC_SCALA0(Line, intercept_v, { return r.y - r.x * slope(); })
  FUNC_SCALA0(Line, intercept_h, { return r.x - r.y * slope_inv(); })
  FUNC_SCALA1(Line, lerp_y, data_t, x, { return l.y + (x - l.x) * slope(); })
  FUNC_SCALA1(Line, lerp_x, data_t, y, {
    return l.x + (y - l.y) * slope_inv();
  })
  friend constexpr bool is_parallel(const Line &lhs, const Line &rhs) {
    return is_zero(cross_mul(lhs.direction(), rhs.direction()));
  }
  friend constexpr bool is_same_dir(const Line &lhs, const Line &rhs) {
    return is_parallel(lhs, rhs) &&
           is_positive(dot_mul(lhs.direction(), rhs.direction()));
  }
  constexpr Point direction() const { return r - l; }
  constexpr bool is_include_strict(const Point &p) const {
    return is_positive(cross(l, r, p));
  }
  constexpr bool is_include(const Point &p) const {
    return !is_negative(cross(l, r, p));
  }
  FNUC_SELF1(Line, push, data_t, dist, {
    Point delta = direction().do_rot90().do_unit();
    delta *= dist;
    l += delta;
    r += delta;
    return *this;
  })
};
constexpr bool is_ins_LL(const Line &l1, const Line &l2) {
  return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r));
}
constexpr Point ins_LL(const Line &l1, const Line &l2) {
  data_t a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}
constexpr bool is_ins_SS(const Line &l1, const Line &l2) {
  return is_intersect(l1.l.x, l1.r.x, l2.l.x, l2.r.x) &&
         is_intersect(l1.l.y, l1.r.y, l2.l.y, l2.r.y) &&
         sgn_cross(l1.l, l1.r, l2.l) * sgn_cross(l1.l, l1.r, l2.r) <= 0 &&
         sgn_cross(l2.l, l2.r, l1.l) * sgn_cross(l2.l, l2.r, l1.r) <= 0;
}
constexpr bool is_ins_SS_strict(const Line &s1, const Line &s2) {
  return sgn_cross(s1.l, s1.r, s2.l) * sgn_cross(s1.l, s1.r, s2.r) < 0 &&
         sgn_cross(s2.l, s2.r, s1.l) * sgn_cross(s2.l, s2.r, s1.r) < 0;
}
constexpr Point proj(const Line &l1, const Point &p) {
  Point dir = l1.direction();
  return l1.l + dir * (dot_mul(dir, p - l1.l) / dir.norm());
}
constexpr Point reflect(const Line &l1, const Point &p) {
  return proj(l1, p) * 2 - p;
}
constexpr bool is_on_same_L(const Point &p1, const Point &p2, const Point &p3) {
  return is_zero(cross(p1, p2, p3));
}
constexpr bool is_on_S(const Line &s1, const Point &p) {
  return is_on_same_L(s1.l, s1.r, p) && is_in_middle(s1.l, p, s1.r);
}
constexpr bool is_on_S_strict(const Line &s1, const Point &p) {
  return sgn_cross(s1.l, s1.r, p) == 0 &&
         sgn(dot_mul(p - s1.l, s1.l - s1.r)) *
             sgn(dot_mul(p - s1.r, s1.l - s1.r)) <
           0;
}
constexpr data_t dist_PL(const Point &p, const Line &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  return dist_PP(p, proj(s1, p));
}
constexpr data_t dist_PS(const Point &p, const Line &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  Point h = proj(s1, p);
  if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
  return std::min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}
constexpr data_t dist_SS(const Line &s1, const Line &s2) {
  if (is_ins_SS(s1, s2)) return 0;
  return std::min({dist_PS(s1.l, s2),
                   dist_PS(s1.r, s2),
                   dist_PS(s2.l, s1),
                   dist_PS(s2.r, s1)});
}
struct Polygon {
  cont_t<Point> vs;
  Polygon() = default;
  explicit Polygon(size_t size_): vs(size_) {}
  explicit Polygon(const cont_t<Point> &vs_): vs(vs_) {}
  friend std::istream &operator>>(std::istream &is, Polygon &rhs) {
    for (auto &i : rhs.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Polygon &rhs) {
    for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it)
      os << *it << ' ';
    return os << rhs.vs.back();
  }
  Polygon &resort() {
    std::sort(vs.begin(), vs.end());
    return *this;
  }
  void resort_in_clockwise() {
    std::sort(vs.begin(), vs.end(), [](const Point &lhs, const Point &rhs) {
      return lhs.quad() == rhs.quad() ? is_negative(cross_mul(lhs, rhs)) :
                                        lhs.quad() > rhs.quad();
    });
  }
  void resort_in_counterclockwise() {
    std::sort(vs.begin(), vs.end(), [](const Point &lhs, const Point &rhs) {
      return lhs.quad() == rhs.quad() ? is_positive(cross_mul(lhs, rhs)) :
                                        lhs.quad() < rhs.quad();
    });
  }
  Polygon &reunique() {
    resort();
    vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
    return *this;
  }
  Point &operator[](size_t x) { return vs[x]; }
  const Point &operator[](size_t x) const { return vs[x]; }
  cont_t<Point>::const_iterator prev(cont_t<Point>::const_iterator it) const {
    return --(it == vs.begin() ? it = vs.end() : it);
  }
  cont_t<Point>::const_iterator next(cont_t<Point>::const_iterator it) const {
    return ++it == vs.end() ? vs.begin() : it;
  }
  size_t prev(size_t idx) const { return idx == 0 ? vs.size() - 1 : idx - 1; }
  size_t next(size_t idx) const { return idx + 1 == vs.size() ? 0 : idx + 1; }
  virtual RELA_PoP relation_P(const Point &p) const {
    for (auto &&now : vs)
      if (now == p) return RELA_PoP::onendpoint_pop;
    bool result = false;
    for (size_t i = 0; i < vs.size(); ++i) {
      Point now_p = vs[i], next_p = vs[next(i)];
      if (is_on_S({now_p, next_p}, p)) return RELA_PoP::onborder_pop;
      if (!is_greater(now_p.y, next_p.y)) std::swap(now_p, next_p);
      if (is_greater(p.y, now_p.y) || !is_greater(p.y, next_p.y)) continue;
      result ^= sgn_cross(p, now_p, next_p) > 0;
    }
    return result ? RELA_PoP::inside_pop : RELA_PoP::outside_pop;
  }
};
struct ConvexHull: public Polygon {
  ConvexHull() = default;
  explicit ConvexHull(size_t size_): Polygon(size_) {}
  explicit ConvexHull(const cont_t<Point> &vs_,
                      bool inited = false,
                      bool strict = true)
    : Polygon(vs_) {
    if (!inited) strict ? init() : init_nonstrict();
  }
  friend std::istream &operator>>(std::istream &is, ConvexHull &rhs) {
    for (auto &i : rhs.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const ConvexHull &rhs) {
    for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it)
      os << *it << ' ';
    return os << rhs.vs.back();
  }
  ConvexHull &init() {
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return *this;
    resort();
    cont_t<Point> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
      while (sz_cvh > 1 &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
      while (sz_cvh > t &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vs = cvh;
    return *this;
  }
  ConvexHull &init_nonstrict() {
    reunique();
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return *this;
    cont_t<Point> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
      while (sz_cvh > 1 &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
      while (sz_cvh > t &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vs = cvh;
    return *this;
  }
  RELA_PoP relation_P(const Point &p) const override {
    for (auto &&now : vs)
      if (now == p) return RELA_PoP::onendpoint_pop;
    size_t sz = vs.size();
    for (size_t i = 0; i < sz; ++i)
      if (is_on_S({vs[i], vs[next(i)]}, p)) return RELA_PoP::onborder_pop;
    if (sz < 3) return RELA_PoP::outside_pop;
    if (is_positive(cross(vs.front(), p, vs[1])) ||
        is_positive(cross(vs.front(), vs.back(), p)))
      return RELA_PoP::outside_pop;
    auto it =
      std::lower_bound(vs.begin() + 1,
                       vs.end(),
                       p,
                       [&](const Point &lhs, const Point &rhs) {
                         return is_positive(cross(vs.front(), lhs, rhs));
                       }) -
      1;
    auto next_it = next(it);
    auto res = sgn_cross(p, *it, *next_it);
    if (res) return ~res ? RELA_PoP::inside_pop : RELA_PoP::outside_pop;
    return !res && !is_positive(dot(p, *it, *next_it)) ? RELA_PoP::inside_pop :
                                                         RELA_PoP::outside_pop;
  }
};
#undef FUNC_SCALA0
#undef FUNC_iSCALA0
#undef FUNC_SCALA1
#undef FUNC_SELF0
#undef FNUC_SELF1
#undef FNUC_iSELF1
}
using namespace geometry2d;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  read_var_(int, n);
  Polygon pa(n), pb(n);
  cin >> pa >> pb;
  ConvexHull ca(pa.vs), cb(pb.vs);
  cout << count_if(all_(pb.vs),
                   [&](auto &&p) { return ca.relation_P(p) != outside_pop; })
       << ' ' << count_if(all_(pa.vs), [&](auto &&p) {
            return cb.relation_P(p) != outside_pop;
          });
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
