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
constexpr FP dist_PP(point<FP> const &p1, point<FP> const &p2) {
  return (p1 - p2).norm();
}
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
constexpr FP dot(point<FP> const &o, point<FP> const &a, point<FP> const &b) {
  return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
template <class FP>
constexpr int
sgn_dot(point<FP> const &o, point<FP> const &a, point<FP> const &b) {
  return sgn(dot(o, a, b));
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct triangle {
  point<FP> A, B, C;
  triangle() {}
  constexpr triangle(point<FP> const &a, point<FP> const &b, point<FP> const &c)
    : A(a), B(b), C(c) {}
  constexpr triangle(FP a_x, FP a_y, FP b_x, FP b_y, FP c_x, FP c_y)
    : A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}
  friend std::istream &operator>>(std::istream &is, triangle &t) {
    return is >> t.A >> t.B >> t.C;
  }
  friend std::ostream &operator<<(std::ostream &os, triangle const &t) {
    return os << t.A << ' ' << t.B << ' ' << t.C;
  }
  friend bool operator==(triangle const &l, triangle const &r) {
    return l.A == r.A && l.B == r.B && l.C == r.C;
  }
  constexpr FP area() const { return std::abs(cross(A, B, C)) / 2; }
  constexpr point<FP> average_w(FP wA, FP wB, FP wC) const {
    return (A * wA + B * wB + C * wC) / (wA + wB + wC);
  }
  constexpr bool is_acute() const {
    return is_pos(dot(A, B, C)) && is_pos(dot(B, C, A)) && is_pos(dot(C, A, B));
  }
  constexpr bool is_right() const {
    return is_zero(dot(A, B, C)) || is_zero(dot(B, C, A)) ||
           is_zero(dot(C, A, B));
  }
  constexpr bool is_obtuse() const {
    return is_neg(dot(A, B, C)) || is_neg(dot(B, C, A)) || is_neg(dot(C, A, B));
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
constexpr FP radius_I(triangle<FP> const &t) {
  FP ab = dist_PP(t.A, t.B), bc = dist_PP(t.B, t.C), ca = dist_PP(t.C, t.A);
  return 2 * t.area() / (ab + bc + ca);
}
template <class FP>
constexpr point<FP> center_I(triangle<FP> const &t) {
  return t.average_w(
    (t.B - t.C).norm(), (t.C - t.A).norm(), (t.A - t.B).norm());
}
}  // namespace tifa_libs::geo
using tri = tifa_libs::geo::triangle<double>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);
  tri t;
  std::cin >> t;
  std::cout << tifa_libs::geo::center_I(t) << ' ' << tifa_libs::geo::radius_I(t)
            << '\n';
  return 0;
}
