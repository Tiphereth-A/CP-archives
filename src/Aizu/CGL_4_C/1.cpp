#include <bits/stdc++.h>
using u32 = uint32_t;
using usz = size_t;
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
constexpr bool is_ins_LL(line<FP> const &l1, line<FP> const &l2) {
  return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r));
}
template <class FP>
constexpr point<FP> ins_LL(line<FP> const &l1, line<FP> const &l2) {
  FP a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
constexpr FP dist_PP(point<FP> const &p1, point<FP> const &p2) {
  return (p1 - p2).norm();
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct polygon {
  vec<point<FP>> vs;
  polygon() {}
  explicit polygon(usz sz): vs(sz) {}
  explicit polygon(vec<point<FP>> const &vs_): vs(vs_) {}
  friend std::istream &operator>>(std::istream &is, polygon &p) {
    for (auto &i : p.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, polygon const &p) {
    if (p.vs.empty()) return os;
    for (auto it = p.vs.begin(); it != p.vs.end() - 1; ++it) os << *it << ' ';
    return os << p.vs.back();
  }
  polygon &resort() {
    std::sort(vs.begin(), vs.end());
    return *this;
  }
  polygon &reunique() {
    resort();
    vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
    return *this;
  }
  point<FP> &operator[](usz x) { return vs[x]; }
  point<FP> const &operator[](usz x) const { return vs[x]; }
  auto prev(typename vec<point<FP>>::const_iterator it) const {
    return --(it == vs.begin() ? it = vs.end() : it);
  }
  auto next(typename vec<point<FP>>::const_iterator it) const {
    return ++it == vs.end() ? vs.begin() : it;
  }
  usz prev(usz idx) const { return idx == 0 ? vs.size() - 1 : idx - 1; }
  usz next(usz idx) const { return idx + 1 == vs.size() ? 0 : idx + 1; }
  FP circum() const {
    FP ret = dist_PP(vs.back(), vs.front());
    for (usz i = 0; i < vs.size() - 1; ++i) ret += dist_PP(vs[i], vs[i + 1]);
    return ret;
  }
  FP area() const {
    if (vs.size() < 3) return 0;
    FP ret = vs.back() ^ vs.front();
    for (usz i = 0; i < vs.size() - 1; ++i) ret += vs[i] ^ vs[i + 1];
    return ret / 2;
  }
  bool is_convex() const {
    bool flag[2] = {false, false};
    usz n = vs.size();
    if (n < 3) return true;
    for (usz i = 0, j = next(i), k = next(j); i < n;
         ++i, j = next(j), k = next(k)) {
      auto sgn = sgn_cross(vs[i], vs[j], vs[k]);
      if (sgn) flag[(sgn + 1) / 2] = true;
      if (flag[0] && flag[1]) return false;
    }
    return true;
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct cvh: public polygon<FP> {
  cvh() {}
  explicit cvh(usz sz): polygon<FP>(sz) {}
  explicit cvh(vec<point<FP>> const &vs_,
               bool inited = false,
               bool strict = true)
    : polygon<FP>(vs_) {
    if (!inited) strict ? init() : init_nonstrict();
  }
  friend std::istream &operator>>(std::istream &is, cvh &ch) {
    for (auto &i : ch.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, cvh<FP> const &ch) {
    if (ch.vs.empty()) return os;
    for (auto it = ch.vs.begin(); it != ch.vs.end() - 1; ++it) os << *it << ' ';
    return os << ch.vs.back();
  }
  cvh &init() {
    usz n = this->vs.size();
    if (n <= 1) return *this;
    this->resort();
    vec<point<FP>> cvh(n * 2);
    usz sz_cvh = 0;
    for (usz i = 0; i < n; cvh[sz_cvh++] = this->vs[i++])
      while (sz_cvh > 1 &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) <= 0)
        --sz_cvh;
    for (usz i = n - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = this->vs[i--])
      while (sz_cvh > t &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) <= 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    this->vs = cvh;
    return *this;
  }
  cvh &init_nonstrict() {
    this->reunique();
    usz n = this->vs.size();
    if (n <= 1) return *this;
    vec<point<FP>> cvh(n * 2);
    usz sz_cvh = 0;
    for (usz i = 0; i < n; cvh[sz_cvh++] = this->vs[i++])
      while (sz_cvh > 1 &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) < 0)
        --sz_cvh;
    for (usz i = n - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = this->vs[i--])
      while (sz_cvh > t &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) < 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    this->vs = cvh;
    return *this;
  }
  FP diameter() const {
    usz n = this->vs.size();
    if (n <= 1) return FP{};
    usz is = 0, js = 0;
    for (usz k = 1; k < n; ++k) {
      is = this->vs[k] < this->vs[is] ? k : is;
      js = this->vs[js] < this->vs[k] ? k : js;
    }
    usz i = is, j = js;
    FP ret = dist_PP(this->vs[i], this->vs[j]);
    do {
      (++(((this->vs[this->next(i)] - this->vs[i]) ^
           (this->vs[this->next(j)] - this->vs[j])) >= 0 ?
            j :
            i)) %= n;
      ret = std::max(ret, dist_PP(this->vs[i], this->vs[j]));
    } while (i != is || j != js);
    return ret;
  }
  cvh &do_minkowski_sum_nonstrict(cvh<FP> const &r) {
    usz n = this->vs.size(), m = r.vs.size();
    if (!m) return *this;
    if (!n) return *this = r;
    vec<point<FP>> result;
    result.reserve(n + m);
    usz midxl = 0;
    for (usz i = 1; i < n; ++i)
      midxl = this->vs[i] < this->vs[midxl] ? i : midxl;
    usz midxr = 0;
    for (usz i = 1; i < m; ++i) midxr = r[i] < r[midxr] ? i : midxr;
    bool fl = false, fr = false;
    for (usz idxl = midxl, idxr = midxr;
         !(idxl == midxl && fl) || !(idxr == midxr && fr);) {
      point diffl = this->vs[this->next(idxl)] - this->vs[idxl],
            diffr = r[r.next(idxr)] - r[idxr];
      bool f = !(idxl == midxl && fl) &&
               ((idxr == midxr && fr) || is_pos(diffl ^ diffr));
      result.push_back(this->vs[idxl] + r[idxr] + (f ? diffl : diffr));
      (f ? idxl : idxr) = (f ? this->next(idxl) : r.next(idxr));
      (f ? fl : fr) |= !(f ? idxl : idxr);
    }
    this->vs = result;
    return *this;
  }
  cvh &do_minkowski_sum(cvh<FP> const &r) {
    return do_minkowski_sum_nonstrict(r).init();
  }
  cvh &do_ins_CVHhP(line<FP> const &l) {
    usz n = this->vs.size();
    vec<point<FP>> cvc;
    for (usz i = 0; i < n; ++i) {
      point p1 = this->vs[i], p2 = this->vs[this->next(i)];
      int d1 = sgn_cross(l.l, l.r, p1), d2 = sgn_cross(l.l, l.r, p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, l));
    }
    this->vs = cvc;
    return *this;
  }
};
}  // namespace tifa_libs::geo
using cvh = tifa_libs::geo::cvh<double>;
using line = tifa_libs::geo::line<double>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(8);
  u32 n;
  std::cin >> n;
  cvh p(n);
  std::cin >> p;
  p.init();
  u32 q;
  std::cin >> q;
  for (usz i = 0; i < q; ++i) {
    line l;
    std::cin >> l;
    auto _ = p;
    std::cout << _.do_ins_CVHhP(l).area() << '\n';
  }
  return 0;
}
