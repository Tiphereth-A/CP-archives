#include <bits/stdc++.h>
using u32 = uint32_t;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs {
template <class FP>
constexpr FP EPS = 1e-8;
template <class FP>
const FP PI = std::acos((FP)-1);
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
using is_s128 = typename std::conditional<std::is_same_v<T, __int128_t> ||
                                            std::is_same_v<T, __int128>,
                                          std::true_type,
                                          std::false_type>::type;
template <class T>
using is_u128 =
  typename std::conditional<std::is_same_v<T, __uint128_t> ||
                              std::is_same_v<T, unsigned __int128>,
                            std::true_type,
                            std::false_type>::type;
template <class T>
using is_int =
  typename std::conditional_t<std::is_integral_v<T> || is_s128<T>::value ||
                                is_u128<T>::value,
                              std::true_type,
                              std::false_type>;
}  // namespace tifa_libs
namespace tifa_libs {
template <class FP, std::enable_if_t<is_int<FP>::value> * = nullptr>
constexpr int sgn(FP x) {
  return !!x | (x >> (sizeof(FP) * 8 - 1));
}
template <class FP, std::enable_if_t<std::is_floating_point_v<FP>> * = nullptr>
constexpr int sgn(FP x) {
  return (x > EPS<FP>)-(x < -EPS<FP>);
}
template <class FP>
constexpr bool is_neg(FP x) {
  return sgn(x) < 0;
}
template <class FP>
constexpr bool is_zero(FP x) {
  return !sgn(x);
}
template <class FP>
constexpr bool is_pos(FP x) {
  return sgn(x) > 0;
}
template <class FP>
constexpr int comp(FP l, FP r) {
  return sgn(l - r);
}
template <class FP>
constexpr bool is_lt(FP l, FP r) {
  return is_neg(l - r);
}
template <class FP>
constexpr bool is_eq(FP l, FP r) {
  return is_zero(l - r);
}
template <class FP>
constexpr bool is_gt(FP l, FP r) {
  return is_pos(l - r);
}
}  // namespace tifa_libs
namespace tifa_libs::geo {
template <class FP>
struct point {
  FP x, y;
  explicit constexpr point(FP x = FP{}, FP y = FP{}): x(x), y(y) {}
  friend std::istream &operator>>(std::istream &is, point &p) {
    return is >> p.x >> p.y;
  }
  friend std::ostream &operator<<(std::ostream &os, point const &p) {
    return os << p.x << ' ' << p.y;
  }
  friend constexpr point lerp(point const &s, point const &t, FP r) {
    return s * r + t * (1 - r);
  }
  friend constexpr point mid_point(point const &s, point const &t) {
    return lerp(s, t, 0.5);
  }
  constexpr point &operator+=(FP n) {
    this->x += n;
    this->y += n;
    return *this;
  }
  constexpr point operator+(FP n) const { return point(*this) += n; }
  constexpr point &operator-=(FP n) {
    this->x -= n;
    this->y -= n;
    return *this;
  }
  constexpr point operator-(FP n) const { return point(*this) -= n; }
  constexpr point &operator*=(FP n) {
    this->x *= n;
    this->y *= n;
    return *this;
  }
  constexpr point operator*(FP n) const { return point(*this) *= n; }
  constexpr point &operator/=(FP n) {
    this->x /= n;
    this->y /= n;
    return *this;
  }
  constexpr point operator/(FP n) const { return point(*this) /= n; }
  constexpr point &operator+=(point const &p) {
    this->x += p.x;
    this->y += p.y;
    return *this;
  }
  constexpr point operator+(point const &p) const { return point(*this) += p; }
  constexpr point &operator-=(point const &p) {
    this->x -= p.x;
    this->y -= p.y;
    return *this;
  }
  constexpr point operator-(point const &p) const { return point(*this) -= p; }
  constexpr point operator-() const { return point{-x, -y}; }
  constexpr bool operator<(point const &p) const {
    if (auto c = comp(x, p.x); c) return c >> 1;
    return comp(y, p.y) >> 1;
  }
  constexpr bool operator==(point const &p) const {
    return is_eq(x, p.x) && is_eq(y, p.y);
  }
  constexpr bool operator!=(point const &p) const { return !(*this == p); }
  constexpr FP operator*(point const &p) const { return x * p.x + y * p.y; }
  constexpr FP operator^(point const &p) const { return x * p.y - y * p.x; }
  constexpr auto arg() const { return std::atan2(y, x); }
  constexpr FP arg2pi() const {
    FP _ = arg();
    return is_neg(_) ? _ + 2 * PI<FP> : _;
  }
  constexpr FP norm2() const { return x * x + y * y; }
  constexpr FP norm() const { return std::hypot(x, y); }
  static constexpr u32 QUAD__[9] = {6, 7, 8, 5, 0, 1, 4, 3, 2};
  constexpr u32 quad() const { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; }
  constexpr point &do_rot90() {
    FP tmp = x;
    x = -y;
    y = tmp;
    return *this;
  }
  friend constexpr point rot90(point p) { return p.do_rot90(); }
  constexpr point &do_rot270() {
    FP tmp = y;
    y = -x;
    x = tmp;
    return *this;
  }
  friend constexpr point rot270(point p) { return p.do_rot270(); }
  constexpr point &do_unit() { return *this /= norm(); }
  constexpr point &do_rot(FP theta) {
    FP x0 = x, y0 = y, ct = std::cos(theta), st = std::sin(theta);
    x = x0 * ct - y0 * st;
    y = x0 * st + y0 * ct;
    return *this;
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct circle {
  point<FP> o;
  FP r;
  circle() {}
  constexpr circle(point<FP> const &c, FP r): o(c), r(r) {}
  constexpr circle(FP c_x, FP c_y, FP r_): o(c_x, c_y), r(r_) {}
  friend std::istream &operator>>(std::istream &is, circle &c) {
    return is >> c.o >> c.r;
  }
  friend std::ostream &operator<<(std::ostream &os, circle const &c) {
    return os << c.o << ' ' << c.r;
  }
  friend bool operator==(circle const &l, circle const &r) {
    return l.o == r.o && l.r == r.r;
  }
  constexpr FP area(FP angle = PI<FP> * 2) const { return angle * r * r / 2; }
  constexpr FP crown_area(FP angle = PI<FP> * 2) const {
    return (angle - std::sin(angle)) * r * r / 2;
  }
  constexpr FP arc(FP angle = PI<FP> * 2) const { return angle * r; }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
constexpr FP cross(point<FP> const &o, point<FP> const &a, point<FP> const &b) {
  return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
template <class FP>
constexpr int
sgn_cross(point<FP> const &o, point<FP> const &a, point<FP> const &b) {
  return sgn(cross(o, a, b));
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct line {
  point<FP> l, r;
  line() {}
  constexpr line(point<FP> const &s, point<FP> const &t): l(s), r(t) {}
  constexpr line(FP s_x, FP s_y, FP t_x, FP t_y): l(s_x, s_y), r(t_x, t_y) {}
  friend std::istream &operator>>(std::istream &is, line &l) {
    return is >> l.l >> l.r;
  }
  friend std::ostream &operator<<(std::ostream &os, line const &l) {
    return os << l.l << ' ' << l.r;
  }
  constexpr point<FP> direction() const { return r - l; }
  constexpr bool is_parallel(line const &r) const {
    return is_zero(direction() ^ r.direction());
  }
  friend constexpr bool is_parallel(line const &l, line const &r) {
    return l.is_parallel(r);
  }
  constexpr bool is_same_dir(line const &r) const {
    return is_parallel(r) && is_pos(direction() * r.direction());
  }
  friend constexpr bool is_same_dir(line const &l, line const &r) {
    return l.is_same_dir(r);
  }
  constexpr friend bool operator<(line const &l, line const &r) {
    if (l.is_same_dir(r)) return r.is_include_strict(l.l);
    auto vl = l.direction(), vr = r.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_pos(vl ^ vr);
  }
  friend bool operator==(line const &l, line const &r) {
    return l.l == r.l && l.r == r.r;
  }
  constexpr FP slope() const { return (r.y - l.y) / (r.x - l.x); }
  constexpr FP slope_inv() const { return (r.x - l.x) / (r.y - l.y); }
  constexpr FP intercept_v() const { return r.y - r.x * slope(); }
  constexpr FP intercept_h() const { return r.x - r.y * slope_inv(); }
  constexpr FP lerp_y(FP x) const { return l.y + (x - l.x) * slope(); }
  constexpr FP lerp_x(FP y) const { return l.x + (y - l.y) * slope_inv(); }
  constexpr bool is_include_strict(point<FP> const &p) const {
    return is_pos(cross(l, r, p));
  }
  constexpr bool is_include(point<FP> const &p) const {
    return !is_neg(cross(l, r, p));
  }
  constexpr line &do_push(FP dist) {
    point delta = direction().do_rot90().do_unit() * dist;
    l += delta;
    r += delta;
    return *this;
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
std::optional<ptt<point<FP>>> tan_CP(circle<FP> const &c, point<FP> const &p) {
  point v = p - c.o;
  FP x = v.norm2(), d = x - c.r * c.r;
  if (is_neg(d)) return {};
  point q1 = c.o + v * (c.r * c.r / x);
  point q2 = v.do_rot90() * (c.r * std::sqrt(d) / x);
  return ptt<point<FP>>{q1 - q2, q1 + q2};
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
std::optional<ptt<line<FP>>> extan_CC(circle<FP> const &c1,
                                      circle<FP> const &c2) {
  if (is_eq(c1.o.x, c2.o.x) && is_eq(c1.o.y, c2.o.y)) return {};
  if (is_eq(c1.r, c2.r)) {
    point dr = (c2.o - c1.o).do_unit().do_rot90() * c1.r;
    return ptt<line<FP>>{{c1.o + dr, c2.o + dr}, {c1.o - dr, c2.o - dr}};
  }
  point p = (c2.o * c1.r - c1.o * c2.r) / (c1.r - c2.r);
  auto ps = tan_CP(c1, p), qs = tan_CP(c2, p);
  if (!ps.has_value() || !qs.has_value()) return {};
  return ptt<line<FP>>{{ps.value().first, qs.value().first},
                       {ps.value().second, qs.value().second}};
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
std::optional<ptt<line<FP>>> intan_CC(circle<FP> const &c1,
                                      circle<FP> const &c2) {
  if (is_eq(c1.o.x, c2.o.x) && is_eq(c1.o.y, c2.o.y)) return {};
  point p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
  auto ps = tan_CP(c1, p), qs = tan_CP(c2, p);
  if (!ps.has_value() || !qs.has_value()) return {};
  return ptt<line<FP>>{{ps.value().first, qs.value().first},
                       {ps.value().second, qs.value().second}};
}
}  // namespace tifa_libs::geo
using point = tifa_libs::geo::point<double>;
using circ = tifa_libs::geo::circle<double>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);
  circ c1, c2;
  std::cin >> c1 >> c2;
  auto exl = extan_CC(c1, c2), inl = intan_CC(c1, c2);
  vec<point> ans;
  if (exl.has_value()) {
    ans.push_back(exl.value().first.l);
    ans.push_back(exl.value().second.l);
  }
  if (inl.has_value()) {
    ans.push_back(inl.value().first.l);
    ans.push_back(inl.value().second.l);
  }
  std::sort(ans.begin(), ans.end());
  ans.erase(std::unique(ans.begin(), ans.end()), ans.end());
  for (auto &i : ans) std::cout << i << '\n';
  return 0;
}
