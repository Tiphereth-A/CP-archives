#include <bits/stdc++.h>
#define CEXP constexpr
#define TPN typename
#define CR const &
#define cT_(...)                                            \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t), \
                     __VA_ARGS__,                           \
                     __VA_ARGS__ CR>
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;
using f64 = double;
using f128 = long double;
template <class T, usz N>
using arr = std::array<T, N>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class U, class T>
using vecp = vec<std::pair<U, T>>;
template <class U, class T>
using vvecp = vvec<std::pair<U, T>>;
template <class T>
using pqg = std::priority_queue<T, vec<T>, std::greater<T>>;
using vecu = vec<u32>;
using vecb = vec<bool>;
using namespace std::literals;
CEXP i8 operator""_i8(unsigned long long x) { return (i8)x; }
CEXP i16 operator""_i16(unsigned long long x) { return (i16)x; }
CEXP i32 operator""_i32(unsigned long long x) { return (i32)x; }
CEXP i64 operator""_i64(unsigned long long x) { return (i64)x; }
CEXP isz operator""_iz(unsigned long long x) { return (isz)x; }
CEXP u8 operator""_u8(unsigned long long x) { return (u8)x; }
CEXP u16 operator""_u16(unsigned long long x) { return (u16)x; }
CEXP u32 operator""_u32(unsigned long long x) { return (u32)x; }
CEXP u64 operator""_u64(unsigned long long x) { return (u64)x; }
CEXP usz operator""_uz(unsigned long long x) { return (usz)x; }
inline const auto fn_0 = [](auto &&...) {};
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
using std::numbers::pi_v;
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
concept iterable_c = requires(T v) {
  { v.begin() } -> std::same_as<TPN T::iterator>;
  { v.end() } -> std::same_as<TPN T::iterator>;
};
template <class T>
concept container_c =
  iterable_c<T> &&
  !std::derived_from<T, std::basic_string<TPN T::value_type>> &&
  !std::derived_from<T, std::basic_string_view<TPN T::value_type>>;
template <class T>
CEXP bool is_char_v =
  std::is_same_v<T, char> || std::is_same_v<T, signed char> ||
  std::is_same_v<T, unsigned char>;
template <class T>
concept char_c = is_char_v<T>;
template <class T>
CEXP bool is_s128_v =
  std::is_same_v<T, __int128_t> || std::is_same_v<T, __int128>;
template <class T>
concept s128_c = is_s128_v<T>;
template <class T>
CEXP bool is_u128_v =
  std::is_same_v<T, __uint128_t> || std::is_same_v<T, unsigned __int128>;
template <class T>
concept u128_c = is_u128_v<T>;
template <class T>
CEXP bool is_i128_v = is_s128_v<T> || is_u128_v<T>;
template <class T>
concept i128_c = is_u128_v<T>;
template <class T>
CEXP bool is_int_v = std::is_integral_v<T> || is_i128_v<T>;
template <class T>
concept int_c = is_int_v<T>;
template <class T>
CEXP bool is_sint_v = is_s128_v<T> || (is_int_v<T> && std::is_signed_v<T>);
template <class T>
concept sint_c = is_sint_v<T>;
template <class T>
CEXP bool is_uint_v = is_u128_v<T> || (is_int_v<T> && std::is_unsigned_v<T>);
template <class T>
concept uint_c = is_uint_v<T>;
template <class T>
concept mint_c = requires(T x) {
  { x.mod() } -> uint_c;
  { x.val() } -> uint_c;
};
template <class T>
concept dft_c = requires(T x, vec<TPN T::data_t> v, u32 n) {
  { x.size() } -> std::same_as<u32>;
  x.bzr(n);
  x.dif(v, n);
  x.dit(v, n);
};
template <class T>
concept ntt_c = dft_c<T> && requires(T x) {
  T::max_size;
  T::G;
};
template <class T>
CEXP bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
template <class T>
concept arithm_c = is_arithm_v<T>;
template <class T>
struct to_sint: std::make_signed<T> {};
template <>
struct to_sint<u128> {
  using type = u128;
};
template <>
struct to_sint<i128> {
  using type = u128;
};
template <class T>
struct to_uint: std::make_unsigned<T> {};
template <>
struct to_uint<u128> {
  using type = u128;
};
template <>
struct to_uint<i128> {
  using type = u128;
};
}  // namespace tifa_libs
namespace tifa_libs {
template <iterable_c T = vec<int>>
CEXP T uniq(T v) {
  std::sort(v.begin(), v.end());
  auto [f, l] = std::ranges::unique(v);
  v.erase(f, l);
  return v;
}
template <iterable_c T = vec<int>>
CEXP std::pair<T, vec<u32>> gen_id(T CR v) {
  const T _ = uniq(v);
  vec<u32> _1;
  _1.reserve(v.size());
  flt_(u32, i, 0, (u32)v.size())
    _1.push_back(u32(std::ranges::lower_bound(_, v[i]) - _.begin()));
  return {_, _1};
}
}  // namespace tifa_libs
namespace tifa_libs {
template <sint_c T>
CEXP int sgn(T x) {
  return (!!x) | (x >> (sizeof(T) * 8 - 1));
}
template <uint_c T>
CEXP int sgn(T x) {
  return !!x;
}
template <std::floating_point FP>
CEXP int sgn(FP x) {
  return (x > eps_v<FP>)-(x < -eps_v<FP>);
}
template <class FP>
CEXP bool is_neg(FP x) {
  return sgn(x) < 0;
}
template <class FP>
CEXP bool is_zero(FP x) {
  return !sgn(x);
}
template <class FP>
CEXP bool is_pos(FP x) {
  return sgn(x) > 0;
}
template <int_c T>
CEXP int comp(T l, T r) {
  return sgn(l - r);
}
template <std::floating_point FP>
CEXP int comp(FP l, FP r) {
  return sgn((l - r) / max({abs(l), abs(r), FP(1)}));
}
template <class FP>
CEXP bool is_lt(FP l, FP r) {
  return comp(l, r) < 0;
}
template <class FP>
CEXP bool is_eq(FP l, FP r) {
  return !comp(l, r);
}
template <class FP>
CEXP bool is_gt(FP l, FP r) {
  return comp(l, r) > 0;
}
}  // namespace tifa_libs
namespace tifa_libs::geo {
template <class FP>
struct point {
  FP x, y;
  explicit CEXP point(FP x = FP{}, FP y = FP{}): x(x), y(y) {}
  friend std::istream &operator>>(std::istream &is, point &p) {
    return is >> p.x >> p.y;
  }
  friend std::ostream &operator<<(std::ostream &os, point CR p) {
    return os << p.x << ' ' << p.y;
  }
  template <std::floating_point T>
  friend CEXP point lerp(point CR s, point CR t, T r) {
    return s * r + t * (1 - r);
  }
  friend CEXP point mid_point(point CR s, point CR t) { return lerp(s, t, .5); }
  template <arithm_c T>
  CEXP point &operator+=(T n) {
    this->x += n, this->y += n;
    return *this;
  }
  template <arithm_c T>
  CEXP point &operator-=(T n) {
    this->x -= n, this->y -= n;
    return *this;
  }
  template <arithm_c T>
  CEXP point &operator*=(T n) {
    this->x *= n, this->y *= n;
    return *this;
  }
  template <arithm_c T>
  CEXP point &operator/=(T n) {
    this->x /= n, this->y /= n;
    return *this;
  }
  template <arithm_c T>
  friend CEXP point operator+(point x, T n) {
    return x += n;
  }
  template <arithm_c T>
  friend CEXP point operator+(T n, point x) {
    return x += n;
  }
  template <arithm_c T>
  friend CEXP point operator-(point x, T n) {
    return x -= n;
  }
  template <arithm_c T>
  friend CEXP point operator-(T n, point x) {
    return x -= n;
  }
  template <arithm_c T>
  friend CEXP point operator*(point x, T n) {
    return x *= n;
  }
  template <arithm_c T>
  friend CEXP point operator*(T n, point x) {
    return x *= n;
  }
  template <arithm_c T>
  friend CEXP point operator/(point x, T n) {
    return x /= n;
  }
  template <arithm_c T>
  friend CEXP point operator/(T n, point x) {
    return x /= n;
  }
  CEXP point &operator+=(point CR p) {
    this->x += p.x, this->y += p.y;
    return *this;
  }
  CEXP point &operator-=(point CR p) {
    this->x -= p.x, this->y -= p.y;
    return *this;
  }
  CEXP point operator+(point CR p) const { return point(*this) += p; }
  CEXP point operator-(point CR p) const { return point(*this) -= p; }
  CEXP point operator-() const { return point{-x, -y}; }
  CEXP auto operator<=>(point CR p) const {
    if (auto CR c = comp(x, p.x); c) return c;
    return comp(y, p.y);
  }
  CEXP bool operator==(point CR p) const {
    return is_eq(x, p.x) && is_eq(y, p.y);
  }
  CEXP FP operator*(point CR p) const { return x * p.x + y * p.y; }
  CEXP FP operator^(point CR p) const { return x * p.y - y * p.x; }
  CEXP FP arg() const {
    static_assert(std::is_floating_point_v<FP>);
    return std::atan2(y, x);
  }
  CEXP FP norm2() const { return x * x + y * y; }
  CEXP FP norm() const {
    static_assert(std::is_floating_point_v<FP>);
    return std::hypot(x, y);
  }
  CEXP point &do_unit() {
    static_assert(std::is_floating_point_v<FP>);
    return *this /= norm();
  }
  static CEXP u32 QUAD__[9] = {6, 7, 8, 5, 0, 1, 4, 3, 2};
  CEXP u32 quad() const { return QUAD__[(sgn(y) + 1) * 3 + sgn(x) + 1]; }
  CEXP int toleft(point CR p) const { return sgn(*this ^ p); }
  CEXP point &do_rot(FP theta) {
    const FP x0 = x, y0 = y, ct = std::cos(theta), st = std::sin(theta);
    x = x0 * ct - y0 * st, y = x0 * st + y0 * ct;
    return *this;
  }
  friend CEXP point rot(point p, FP theta) { return p.do_rot(theta); }
  CEXP point &do_rot90() {
    const FP _ = x;
    x = -y, y = _;
    return *this;
  }
  friend CEXP point rot90(point p) { return p.do_rot90(); }
  CEXP point &do_rot270() {
    const FP _ = y;
    y = -x, x = _;
    return *this;
  }
  friend CEXP point rot270(point p) { return p.do_rot270(); }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
CEXP FP cross(point<FP> CR o, point<FP> CR a, point<FP> CR b) {
  return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
template <std::floating_point FP>
CEXP FP cross_unit(point<FP> CR o, point<FP> CR a, point<FP> CR b) {
  return (a - o).do_unit() ^ (b - o).do_unit();
}
template <std::floating_point FP>
CEXP int sgn_cross(point<FP> CR o, point<FP> CR a, point<FP> CR b) {
  return sgn(cross_unit(o, a, b));
}
template <class FP>
CEXP int sgn_cross(point<FP> CR o, point<FP> CR a, point<FP> CR b) {
  return sgn(cross(o, a, b));
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct line {
  point<FP> l, r;
  CEXP line() {}
  CEXP line(point<FP> CR s, point<FP> CR t): l(s), r(t) {}
  CEXP line(point<FP> CR s, FP angle_x)
    : l(s),
      r(s + is_eq(angle_x, pi_v<FP> / 2) ? point<FP>{0, 1} :
                                           point<FP>{1, std::tan(angle_x)}) {
    assert(angle_x > 0 && angle_x < pi_v<FP>);
  }
  CEXP line(FP a, FP b, FP c) {
    if (is_zero(a)) l = {0, -c / b}, r = {1, -c / b};
    else if (is_zero(b)) l = {-c / a, 0}, r = {-c / a, 1};
    else l = {0, -c / b}, r = {1, -(c + a) / b};
  }
  CEXP line(FP s_x, FP s_y, FP t_x, FP t_y): l(s_x, s_y), r(t_x, t_y) {}
  friend std::istream &operator>>(std::istream &is, line &l) {
    return is >> l.l >> l.r;
  }
  friend std::ostream &operator<<(std::ostream &os, line CR l) {
    return os << l.l << ' ' << l.r;
  }
  CEXP point<FP> direction() const { return r - l; }
  CEXP bool is_parallel(line CR r) const {
    return is_zero(direction() ^ r.direction());
  }
  friend CEXP bool is_parallel(line CR l, line CR r) {
    return l.is_parallel(r);
  }
  CEXP bool is_same_dir(line CR r) const {
    return is_parallel(r) && is_pos(direction() * r.direction());
  }
  friend CEXP bool is_same_dir(line CR l, line CR r) {
    return l.is_same_dir(r);
  }
  friend CEXP bool operator==(line CR l, line CR r) {
    return l.l == r.l && l.r == r.r;
  }
  friend CEXP auto operator<=>(line CR l, line CR r) {
    if (l == r) return 0;
    if (l.is_same_dir(r)) return r.is_include_strict(l.l) ? -1 : 1;
    const auto vl = l.direction(), vr = r.direction();
    if (vl.quad() != vr.quad()) return (i32)vl.quad() - (i32)vr.quad();
    return -sgn(vl ^ vr);
  }
  CEXP int toleft(point<FP> CR p) const { return sgn_cross(l, r, p); }
  CEXP bool is_include_strict(point<FP> CR p) const { return toleft(p) > 0; }
  CEXP bool is_include(point<FP> CR p) const { return toleft(p) >= 0; }
  CEXP line &do_push(FP dist) {
    const point delta = direction().do_rot90().do_unit() * dist;
    l += delta, r += delta;
    return *this;
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
CEXP bool is_ins_LL(line<FP> CR l1, line<FP> CR l2) {
  return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r));
}
template <class FP>
CEXP point<FP> ins_LL(line<FP> CR l1, line<FP> CR l2) {
  const FP a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}
template <class FP>
CEXP point<FP> ins_LL(line<FP> CR l, FP a, FP b, FP c) {
  const FP a1 = abs(a * l.l.x + b * l.l.y + c),
           a2 = abs(a * l.r.x + b * l.r.y + c);
  return (l.l * a2 + l.r * a1) / (a1 + a2);
}
}  // namespace tifa_libs::geo
namespace tifa_libs::math {
template <std::floating_point FP>
class kahan_fp {
  FP sum, c;

public:
  CEXP kahan_fp(FP val = 0): sum(val), c(0) {}
  CEXP kahan_fp &operator+=(FP x) {
    const FP y = x - c;
    volatile FP t = sum + y, z = t - sum;
    c = z - y, sum = t;
    return *this;
  }
  CEXP operator FP() const { return sum; }
};
template <class FP>
using kahan =
  std::conditional_t<std::is_floating_point_v<FP>, kahan_fp<FP>, FP>;
}  // namespace tifa_libs::math
namespace tifa_libs::geo {
template <class FP>
CEXP FP dist_PP_Ma(point<FP> CR p1, point<FP> CR p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
template <class FP>
CEXP FP dist_PP(point<FP> CR p1, point<FP> CR p2) {
  return (p1 - p2).norm();
}
template <class FP>
CEXP FP dist_PP_Ch(point<FP> CR p1, point<FP> CR p2) {
  return max(abs(p1.x - p2.x), abs(p1.y - p2.y));
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct polygon {
  vec<point<FP>> vs;
  CEXP polygon() {}
  explicit CEXP polygon(u32 sz): vs(sz) {}
  explicit CEXP polygon(vec<point<FP>> CR vs_): vs(vs_) {}
  friend std::istream &operator>>(std::istream &is, polygon &p) {
    for (auto &i : p.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, polygon CR p) {
    if (p.vs.empty()) return os;
    for (auto it = p.vs.begin(); it != p.vs.end() - 1; ++it) os << *it << ' ';
    return os << p.vs.back();
  }
  CEXP u32 size() const { return (u32)vs.size(); }
  CEXP point<FP> &operator[](u32 x) { return vs[x]; }
  CEXP point<FP> CR operator[](u32 x) const { return vs[x]; }
  CEXP polygon &resort() {
    std::ranges::sort(vs);
    return *this;
  }
  CEXP polygon &reunique() {
    vs = uniq(vs);
    return *this;
  }
  CEXP auto prev(TPN vec<point<FP>>::const_iterator it) const {
    return --(it == vs.begin() ? it = vs.end() : it);
  }
  CEXP auto next(TPN vec<point<FP>>::const_iterator it) const {
    return ++it == vs.end() ? vs.begin() : it;
  }
  CEXP u32 prev(u32 idx) const { return idx == 0 ? size() - 1 : idx - 1; }
  CEXP u32 next(u32 idx) const { return idx + 1 == size() ? 0 : idx + 1; }
  CEXP FP circum() const {
    math::kahan<FP> ret = dist_PP(vs.back(), vs.front());
    flt_(u32, i, 0, size() - 1) ret += dist_PP(vs[i], vs[i + 1]);
    return ret;
  }
  CEXP FP area2() const {
    if (size() < 3) return 0;
    math::kahan<FP> ret = vs.back() ^ vs.front();
    flt_(u32, i, 0, size() - 1) ret += vs[i] ^ vs[i + 1];
    return ret;
  }
  CEXP f128 area() const { return area2() * .5l; }
  CEXP bool is_convex() const {
    bool flag[2] = {false, false};
    const u32 n = size();
    if (n < 3) return true;
    for (u32 i = 0, j = next(i), k = next(j); i < n;
         ++i, j = next(j), k = next(k)) {
      auto sgn = sgn_cross(vs[i], vs[j], vs[k]);
      if (sgn) flag[(sgn + 1) / 2] = true;
      if (flag[0] && flag[1]) return false;
    }
    return true;
  }
  CEXP std::optional<u32> winding(point<FP> CR p) const {
    u32 cnt = 0;
    flt_(u32, i, 0, size()) {
      auto &&u = vs[i], &&v = vs[next(i)];
      if (!sgn_cross(p, u, v) && !sgn_dot(p, u, v)) return {};
      if (is_zero(u.y - v.y)) continue;
      if (is_lt(u.y, v.y) && !is_pos(u, v, p)) continue;
      if (is_gt(u.y, v.y) && !is_neg(u, v, p)) continue;
      if (is_lt(u.y, p.y) && !is_lt(v.y, p.y)) ++cnt;
      if (!is_lt(u.y, p.y) && is_lt(v.y, p.y)) --cnt;
    }
    return cnt;
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct cvh: public polygon<FP> {
  CEXP cvh() {}
  explicit CEXP cvh(u32 sz): polygon<FP>(sz) {}
  explicit CEXP
  cvh(vec<point<FP>> CR vs_, bool inited = false, bool strict = true)
    : polygon<FP>(vs_) {
    if (!inited) strict ? init<true>() : init<false>();
  }
  friend std::istream &operator>>(std::istream &is, cvh &ch) {
    for (auto &i : ch.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, cvh<FP> CR ch) {
    if (ch.vs.empty()) return os;
    for (auto it = ch.vs.begin(); it != ch.vs.end() - 1; ++it) os << *it << ' ';
    return os << ch.vs.back();
  }
  template <bool strict = true>
  CEXP cvh &init() {
    this->reunique();
    const u32 n = this->size();
    if (n <= 1) return *this;
    vec<point<FP>> cvh(n * 2);
    u32 sz_cvh = 0;
    for (u32 i = 0; i < n; cvh[sz_cvh++] = this->vs[i++])
      if CEXP (strict)
        while (sz_cvh > 1 &&
               sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) <= 0)
          --sz_cvh;
      else
        while (sz_cvh > 1 &&
               sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) < 0)
          --sz_cvh;
    for (u32 i = n - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = this->vs[i--])
      if CEXP (strict)
        while (sz_cvh > t &&
               sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) <= 0)
          --sz_cvh;
      else
        while (sz_cvh > t &&
               sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], this->vs[i]) < 0)
          --sz_cvh;
    cvh.resize(sz_cvh - 1);
    this->vs = cvh;
    return *this;
  }
  CEXP FP diameter() const {
    const u32 n = this->size();
    if (n <= 1) return FP{};
    u32 is = 0, js = 0;
    flt_(u32, k, 1, n) {
      is = this->vs[k] < this->vs[is] ? k : is;
      js = this->vs[js] < this->vs[k] ? k : js;
    }
    u32 i = is, j = js;
    FP ret = dist_PP(this->vs[i], this->vs[j]);
    do {
      (++(((this->vs[this->next(i)] - this->vs[i]) ^
           (this->vs[this->next(j)] - this->vs[j])) >= 0 ?
            j :
            i)) %= n;
      ret = max(ret, dist_PP(this->vs[i], this->vs[j]));
    } while (i != is || j != js);
    return ret;
  }
  CEXP cvh &do_minkowski_sum_nonstrict(cvh<FP> CR r) {
    const u32 n = this->size(), m = r.size();
    if (!m) return *this;
    if (!n) return *this = r;
    vec<point<FP>> result;
    result.reserve(n + m);
    u32 midxl = 0;
    flt_(u32, i, 1, n) midxl = this->vs[i] < this->vs[midxl] ? i : midxl;
    u32 midxr = 0;
    flt_(u32, i, 1, m) midxr = r[i] < r[midxr] ? i : midxr;
    bool fl = false, fr = false;
    for (u32 idxl = midxl, idxr = midxr;
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
  CEXP cvh &do_minkowski_sum(cvh<FP> CR r) {
    return do_minkowski_sum_nonstrict(r).init();
  }
  CEXP cvh &do_ins_CVHhP(line<FP> CR l) {
    const u32 n = this->size();
    vec<point<FP>> cvc;
    flt_(u32, i, 0, n) {
      point p1 = this->vs[i], p2 = this->vs[this->next(i)];
      int d1 = l.toleft(p1), d2 = l.toleft(p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, l));
    }
    this->vs = cvc;
    return *this;
  }
  template <class F>
  requires requires(F f, point<FP> i, point<FP> ni, point<FP> j) {
    f(i, ni, j);
  }
  CEXP void rotcaliper(F &&f) const {
    auto CR p = this->vs;
    for (u32 i = 0, j = 1; i < p.size(); ++i) {
      auto ni = this->next(i);
      f(p[i], p[ni], p[j]);
      while (
        !is_lt(cross(p[ni], p[this->next(j)], p[i]) - cross(p[ni], p[j], p[i])))
        f(p[i], p[ni], p[j = this->next(j)]);
    }
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
CEXP cvh<FP> ins_hPs(vec<line<FP>> vl) {
  auto check = [](line<FP> CR u, line<FP> CR v, line<FP> CR w) -> bool {
    return w.is_include_strict(ins_LL(u, v));
  };
  if ((vl = uniq(vl)).size() < 3) return {};
  std::deque<line<FP>> q;
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
  vec<point<FP>> ret;
  flt_(u32, i, 0, (u32)q.size())
    ret.push_back(ins_LL(q[i], q[(i + 1) % q.size()]));
  return cvh{ret, true};
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
CEXP point<FP> proj(line<FP> CR l, point<FP> CR p) {
  const point dir = l.direction();
  return l.l + dir * (dir * (p - l.l) / dir.norm2());
}
template <class FP>
CEXP point<FP> reflect(line<FP> CR l, point<FP> CR p) {
  return proj(l, p) * 2 - p;
}
}  // namespace tifa_libs::geo
namespace tifa_libs::ds {
template <std::unsigned_integral K, class V, class C = std::less<K>>
class radix_heap {
  static CEXP u32 B = sizeof(K) * 8;
  static CEXP C comp{};
  arr<vecp<K, V>, B + 1> vs;
  arr<K, B + 1> ms;
  u32 s;
  K last;

public:
  CEXP explicit radix_heap(): s(0), last(0) { std::ranges::fill(ms, K(-1)); }
  CEXP u32 size() const { return s; }
  CEXP bool empty() const { return !s; }
  CEXP void emplace(K key, cT_(V) val) {
    ++s;
    const K b = (K)std::bit_width(key ^ last);
    vs[b].emplace_back(key, val), ms[b] = min(key, ms[b], comp);
  }
  CEXP std::pair<K, V> top() {
    if (!~ms[0]) {
      const u32 idx =
        u32(std::ranges::find_if(ms, [](auto x) { return !!~x; }) - ms.begin());
      last = ms[idx];
      for (auto &p : vs[idx]) {
        const K b = (K)std::bit_width(p.first ^ last);
        vs[b].emplace_back(p), ms[b] = min(p.first, ms[b], comp);
      }
      vs[idx].clear(), ms[idx] = K(-1);
    }
    return vs[0].back();
  }
  CEXP void pop() {
    top(), --s, vs[0].pop_back();
    if (vs[0].empty()) ms[0] = K(-1);
  }
};
template <class K, class V>
using rheap = std::conditional_t<std::unsigned_integral<K>,
                                 ds::radix_heap<K, V>,
                                 pqg<std::pair<K, V>>>;
}  // namespace tifa_libs::ds
namespace tifa_libs::graph {
template <class T, bool with_deg = false>
struct alistw {
  using value_type = vvecp<u32, T>;
  value_type g;
  u32 cnt_arc;
  vecu deg_in;
  explicit CEXP alistw(u32 n = 0): g(n), cnt_arc(0), deg_in(0) {
    if CEXP (with_deg) deg_in.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) {
    g[u].emplace_back(v, w), ++cnt_arc;
    if CEXP (with_deg) ++deg_in[v];
  }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <class T, class F, bool with_deg>
requires(!sint_c<T>) && requires(F relex, u32 now, u32 to) { relex(now, to); }
CEXP vec<T> dijkstra(alistw<T, with_deg> CR fg,
                     u32 s,
                     F &&relax,
                     T INF = std::numeric_limits<T>::max() / 2 - 1) {
  auto &&g = fg.g;
  vec<T> dis(g.size(), INF);
  vecb vis(g.size());
  ds::rheap<T, u32> q;
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, u] = q.top();
    if (dis_now > INF) dis_now = INF;
    q.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : g[u])
      if (dis[u] + w < dis[v]) {
        relax(u, v);
        dis[v] = dis[u] + w;
        if (!vis[v]) q.emplace(dis[v], v);
      }
  }
  return dis;
}
}  // namespace tifa_libs::graph
using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using Line2 = tifa_libs::geo::line<data_t>;
void solve() {
  u32 n;
  std::cin >> n;
  Point2 s, t;
  std::cin >> t >> s;
  vec<Point2> vp(n);
  for (auto &p : vp) std::cin >> p;
  if (!n) {
    std::cout << "0\n";
    return;
  }
  std::map<Point2, u32> ids;
  flt_(u32, i, 0, n) ids[vp[i]] = i + 1;
  u32 pos = 0;
  vecb skip(n);
  {
    data_t len = std::numeric_limits<data_t>::max();
    flt_(u32, i, 0, n) {
      if (vp[i].x > t.x || vp[i].y > t.y) skip[i] = 1;
      if (data_t now = tifa_libs::geo::dist_PP(vp[i], s); len > now)
        len = now, pos = i;
    }
  }
  vec<Line2> vl;
  vl.emplace_back(Point2(0, 0), Point2(t.x, 0));
  vl.emplace_back(Point2(t.x, 0), Point2(t.x, t.y));
  vl.emplace_back(Point2(t.x, t.y), Point2(0, t.y));
  vl.emplace_back(Point2(0, t.y), Point2(0, 0));
  tifa_libs::graph::alistw<u32> g(n + 1);
  flt_(u32, i, 0, n) {
    if (skip[i]) continue;
    vl.resize(4);
    flt_(u32, j, 0, n) {
      if (j == i || skip[j]) continue;
      Point2 mid = mid_point(vp[i], vp[j]), v = rot90(vp[j] - vp[i]);
      vl.emplace_back(mid, mid + v);
    }
    auto res = tifa_libs::geo::ins_hPs(vl);
    flt_(u32, j, 0, res.size()) {
      Line2 l{res.vs[j], res.vs[res.next(j)]};
      u32 id = ids[reflect(l, vp[i])];
      if (id) --id;
      else id = n;
      g.add_arc(i, id, 1);
      g.add_arc(id, i, 1);
    }
  }
  std::cout << tifa_libs::graph::dijkstra(g, pos, fn_0)[n] << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
