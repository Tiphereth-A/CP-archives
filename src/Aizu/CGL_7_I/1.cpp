#include <bits/stdc++.h>
using u32 = uint32_t;
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
constexpr FP dist_PP(point<FP> const &p1, point<FP> const &p2) {
  return (p1 - p2).norm();
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
enum RELCC { lyingin_cc, touchin_cc, intersect_cc, touchex_cc, lyingout_cc };
template <class FP>
constexpr RELCC relation_CC(circle<FP> const &c1, circle<FP> const &c2) {
  FP d = dist_PP(c1.o, c2.o);
  if (is_gt(d, c1.r + c2.r)) return lyingout_cc;
  if (is_eq(d, c1.r + c2.r)) return touchex_cc;
  if (is_gt(d, std::abs(c1.r - c2.r))) return intersect_cc;
  if (is_eq(d, std::abs(c1.r - c2.r))) return touchin_cc;
  return lyingin_cc;
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
constexpr FP area_CC(circle<FP> const &c1, circle<FP> const &c2) {
  auto relation = relation_CC(c1, c2);
  if (relation == RELCC::lyingout_cc || relation == RELCC::touchex_cc)
    return FP{};
  if (relation == RELCC::lyingin_cc || relation == RELCC::touchin_cc)
    return std::min(c1.area(), c2.area());
  FP d = dist_PP(c1.o, c2.o);
  return c1.crown_area(
           std::acos((c1.r * c1.r - c2.r * c2.r + d * d) / (2 * c1.r * d)) *
           2) +
         c2.crown_area(
           std::acos((c2.r * c2.r - c1.r * c1.r + d * d) / (2 * c2.r * d)) * 2);
}
}  // namespace tifa_libs::geo
using circ = tifa_libs::geo::circle<double>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);
  circ c1, c2;
  std::cin >> c1 >> c2;
  std::cout << tifa_libs::geo::area_CC(c1, c2) << '\n';
  return 0;
}
