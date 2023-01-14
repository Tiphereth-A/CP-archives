#include <bits/stdc++.h>
namespace tifa_libs {
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using u128 = __uint128_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
}  // namespace tifa_libs
namespace tifa_libs::math {
constexpr std::tuple<u64, i64, i64> exgcd(i64 a, i64 b) {
  i64 x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b) {
    i64 c = a / b;
    std::tie(x1, x2, x3, x4, a, b) =
      std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
  }
  return {a, x1, x2};
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T, std::enable_if_t<std::is_signed_v<T>, int> = 0>
constexpr T safe_mod(T x, std::make_unsigned_t<T> mod) {
  return ((x %= (T)mod) < 0 ? x + (T)mod : x);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr std::pair<u64, u64> inv_gcd(u64 n, u64 mod) {
  auto [g, x, y] = exgcd((i64)(n % mod), (i64)mod);
  return {g, safe_mod(x, mod)};
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr u64 inverse(u64 n, u64 mod) {
  auto [g, x] = inv_gcd(n % mod, mod);
  assert(g == 1);
  return x;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class Pldt>
class poly {
  Pldt p;

public:
  using value_type = typename Pldt::value_type;
  using data_type = vec<value_type>;
  explicit constexpr poly(size_t sz = 1): p(sz) {}
  explicit constexpr poly(std::initializer_list<value_type> v): p(v) {}
  template <class T>
  explicit constexpr poly(vec<T> const &v): p(v) {}
  constexpr friend std::istream &operator>>(std::istream &is, poly &poly) {
    for (auto &val : poly.p.d) is >> val;
    return is;
  }
  constexpr friend std::ostream &operator<<(std::ostream &os,
                                            const poly &poly) {
    if (!poly.size()) return os;
    for (size_t i = 1; i < poly.size(); ++i) os << poly[i - 1] << ' ';
    return os << poly.p.d.back();
  }
  constexpr size_t size() const { return p.d.size(); }
  constexpr data_type &data() { return p.d; }
  constexpr data_type const &data() const { return p.d; }
  constexpr value_type &operator[](size_t x) { return p.d[x]; }
  constexpr value_type operator[](size_t x) const { return p.d[x]; }
  constexpr value_type operator()(value_type x) const {
    value_type ans = 0;
    for (size_t i = size() - 1; ~i; --i) ans = ans * x + p.d[i];
    return ans;
  }
  template <class F>
  void apply_range(size_t l, size_t r, F f) {
    assert(l < r && r <= size());
    for (size_t i = l; i < r; ++i) f(i, p.d[i]);
  }
  template <class F>
  void apply(F f) {
    apply_range(0, size(), f);
  }
  constexpr void resize(size_t size) { p.d.resize(size); }
  constexpr poly pre(size_t size) const {
    poly _ = *this;
    _.resize(size);
    return _;
  }
  constexpr void strip() {
    auto it = std::find_if(
      p.d.rbegin(), p.d.rend(), [](auto const &x) { return x != 0; });
    p.d.resize(p.d.rend() - it);
    if (p.d.empty()) p.d.push_back(value_type(0));
  }
  constexpr void reverse() { std::reverse(p.d.begin(), p.d.end()); }
  void conv(poly const &r, size_t ans_size) { p.conv(r.p, ans_size); }
  void conv(poly const &r) { p.conv(r.p); }
  constexpr poly operator-() const {
    poly ret = *this;
    ret.apply([]([[maybe_unused]] size_t i, auto &v) { v = -v; });
    return ret;
  }
  friend poly operator+(poly p, value_type c) {
    p[0] += c;
    return p;
  }
  friend poly operator+(value_type c, poly const &p) { return p + c; }
  friend poly operator-(poly p, value_type c) {
    p[0] -= c;
    return p;
  }
  friend poly operator-(value_type c, poly const &p) { return p - c; }
  constexpr poly &operator*=(value_type c) {
    apply([&c]([[maybe_unused]] size_t i, auto &v) { v *= c; });
    return *this;
  }
  constexpr friend poly operator*(poly p, value_type c) { return p *= c; }
  constexpr friend poly operator*(value_type c, poly p) { return p *= c; }
  constexpr poly &operator+=(poly const &r) {
    if (!r.size()) return *this;
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r](size_t i, auto &v) { v += r[i]; });
    return *this;
  }
  friend poly operator+(poly l, poly const &r) { return l += r; }
  constexpr poly &operator-=(poly const &r) {
    if (!r.size()) return *this;
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r](size_t i, auto &v) { v -= r[i]; });
    return *this;
  }
  friend poly operator-(poly l, poly const &r) { return l -= r; }
  poly &operator*=(poly const &r) {
    if (!r.size()) {
      resize(1);
      p.d[0] = 0;
      return *this;
    }
    conv(r);
    return *this;
  }
  friend poly operator*(poly l, poly const &r) { return l *= r; }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
constexpr T qpow(T a, u64 b) {
  T res(1);
  for (; b; b >>= 1, a *= a)
    if (b & 1) res *= a;
  return res;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
inline poly<T> poly_deriv(poly<T> const &p) {
  auto _ = p;
  for (size_t i = 1; i < _.size(); ++i) _[i - 1] = _[i] * i;
  _.data().back() = 0;
  return _;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
inline poly<T> poly_int(poly<T> const &p) {
  using mint = typename T::value_type;
  auto _ = p;
  for (size_t i = _.size() - 1; i; --i) _[i] = _[i - 1] * mint(i).inv();
  _[0] = 0;
  return _;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
inline poly<T> poly_inv(poly<T> const &p, size_t n = 0) {
  assert(p[0] != 0);
  if (!n) n = p.size();
  poly<T> a{p[0].inv()};
  for (size_t i = 1; i < n; i *= 2)
    a = (a * 2 - (a * a * p).pre(i * 2)).pre(i * 2);
  return a.pre(n);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
inline poly<T> poly_ln(poly<T> const &p, size_t n = 0) {
  assert(p[0] == 1);
  if (!n) n = p.size();
  auto _ = poly_deriv(p).pre(n);
  _.conv(poly_inv(p, n));
  return poly_int(_).pre(n);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
inline poly<T> poly_exp(poly<T> const &p, size_t n = 0) {
  assert(p[0] == 0);
  if (!n) n = p.size();
  poly<T> _ = p + 1, a{1};
  for (size_t i = 1; i < n; i *= 2)
    a = (a * (_.pre(i * 2) - poly_ln(a, i * 2))).pre(i * 2);
  return a.pre(n);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
inline poly<T> poly_shl(poly<T> const &p, size_t x) {
  if (!x) return p;
  auto _ = p;
  if (x >= _.size()) {
    std::fill(_.data().begin(), _.data().end(), 0);
    return _;
  }
  std::fill(
    _.data().begin(),
    std::move_backward(_.data().begin(), _.data().end() - x, _.data().end()),
    0);
  return _;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
inline poly<T> poly_shr(poly<T> const &p, size_t x) {
  if (!x) return p;
  auto _ = p;
  if (x >= p.size()) {
    std::fill(_.data().begin(), _.data().end(), 0);
    return _;
  }
  std::fill(std::move(_.data().begin() + x, _.data().end(), _.data().begin()),
            _.data().end(),
            0);
  return _;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
inline poly<T> poly_pow(poly<T> const &p, u64 y, size_t n = 0) {
  using mint = typename T::value_type;
  if (!n) n = p.size();
  if (y == 0) {
    poly<T> _(n);
    if (n) _[0] = 1;
    return _;
  }
  if (y == 1) return p;
  size_t l0 = std::find_if(p.data().begin(),
                           p.data().end(),
                           [](auto const &x) { return x != 0; }) -
              p.data().begin();
  if ((u128)l0 * y >= n) return poly<T>(n);
  if (l0) {
    auto _ = poly_shr(p, l0), g = poly_pow(_, y, n - l0 * y);
    g.resize(n);
    return poly_shl(g, l0 * y);
  }
  auto _ = p;
  mint _0 = p[0];
  if (_0 != 1) _ *= _0.inv();
  _ = poly_exp(poly_ln(_) * y);
  if (_0 != 1) _ *= qpow(_0, y);
  _.resize(n);
  return _;
}
}  // namespace tifa_libs::math
namespace tifa_libs::bit {
template <typename T>
constexpr int cntl0(T x) {
  constexpr int nd = sizeof(T) * 8;
  if (x == 0) return nd;
  static_assert(nd <= 128);
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u) return __builtin_clz(x) - (nd_u - nd);
  else if constexpr (nd <= nd_ul) return __builtin_clzl(x) - (nd_ul - nd);
  else if constexpr (nd <= nd_ull) return __builtin_clzll(x) - (nd_ull - nd);
  else {
    unsigned long long hi = x >> nd_ull;
    if (hi != 0) return __builtin_clzll(hi) - ((2 * nd_ull) - nd);
    unsigned long long lo = x & (unsigned long long)(-1);
    return (nd - nd_ull) + __builtin_clzll(lo);
  }
}
}  // namespace tifa_libs::bit
namespace tifa_libs::bit {
template <typename T>
constexpr int bwidth(T x) {
  return (int)sizeof(T) * 8 - cntl0(x);
}
}  // namespace tifa_libs::bit
namespace tifa_libs::math {
constexpr u64 mul_mod_u(u64 a, u64 b, u64 mod) {
  if (bit::bwidth(a) + bit::bwidth(b) <= 64) return a * b % mod;
  else return (u64)((u128)a * b % mod);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
inline vec<u64> fact_mod_gen(size_t sz, u64 mod) {
  vec<u64> ans(sz, 1);
  for (size_t i = 2; i < sz; ++i) ans[i] = mul_mod_u(ans[i - 1], i, mod);
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
inline vec<u64> inv_mod_gen(size_t sz, u64 mod) {
  vec<u64> ans(sz, 1);
  for (size_t i = 2; i < sz; ++i)
    ans[i] = mul_mod_u(mod - mod / i, ans[mod % i], mod);
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T, bool with_sgn = true>
inline poly<T>
stirling1_col_gen(u64 n, u64 k, vec<u64> const &fact, vec<u64> const &inv) {
  if (n < k) return poly<T>(n + 1);
  poly<T> f(n + 1);
  for (size_t i = 1; i <= n; ++i) f[i] = inv[i];
  f = poly_pow(f, k) * inverse(fact[k], T::value_type::mod());
  for (size_t i = k; i <= n; ++i) f[i] *= fact[i];
  if constexpr (with_sgn)
    for (size_t i = k ^ 1; i <= n; i += 2) f[i] = -f[i];
  return f;
}
template <class T, bool with_sgn = true>
inline poly<T> stirling1_col_gen(u64 n, u64 k) {
  return stirling1_col_gen<T, with_sgn>(
    n,
    k,
    fact_mod_gen(n + 1, T::value_type::mod()),
    inv_mod_gen(n + 1, T::value_type::mod()));
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <u32 MOD>
class mint_s30 {
  u32 v_{};
  static constexpr u32 get_r() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
  }
  static constexpr u32 redc(u64 x) {
    return (u32)((x + (u64)((u32)(x)*R) * MOD) >> 32);
  }
  static constexpr u32 norm(u32 x) {
    return x - (MOD & -((MOD - 1 - x) >> 31));
  }
  static constexpr u32 MOD2 = MOD << 1;
  static constexpr u32 R = get_r();
  static constexpr u32 R2 = -(u64)(MOD) % MOD;
  static constexpr i32 SMOD = (i32)(MOD);
  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);

public:
  static constexpr u32 mod() { return MOD; }
  static constexpr i32 smod() { return SMOD; }
  constexpr mint_s30() {}
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  constexpr mint_s30(T v): v_(redc((u64)(v % SMOD + SMOD) * R2)) {}
  constexpr u32 val() const { return norm(redc(v_)); }
  constexpr i32 sval() const { return (i32)norm(redc(v_)); }
  constexpr bool is_zero() const { return v_ == 0 || v_ == MOD; }
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit constexpr operator T() const {
    return (T)(val());
  }
  constexpr mint_s30 operator-() const {
    mint_s30 res;
    res.v_ = (MOD2 & -(v_ != 0)) - v_;
    return res;
  }
  constexpr mint_s30 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_s30(x1);
  }
  constexpr mint_s30 &operator+=(const mint_s30 &rhs) {
    v_ += rhs.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &operator-=(const mint_s30 &rhs) {
    v_ -= rhs.v_, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &operator*=(const mint_s30 &rhs) {
    v_ = redc((u64)(v_)*rhs.v_);
    return *this;
  }
  constexpr mint_s30 &operator/=(const mint_s30 &rhs) {
    return operator*=(rhs.inv());
  }
  constexpr mint_s30 pow(u64 e) const {
    for (mint_s30 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  constexpr void swap(mint_s30 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend constexpr mint_s30 operator+(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) += rhs;
  }
  friend constexpr mint_s30 operator-(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) -= rhs;
  }
  friend constexpr mint_s30 operator*(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) *= rhs;
  }
  friend constexpr mint_s30 operator/(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) /= rhs;
  }
  friend constexpr bool operator==(const mint_s30 &lhs, const mint_s30 &rhs) {
    return norm(lhs.v_) == norm(rhs.v_);
  }
  friend constexpr bool operator!=(const mint_s30 &lhs, const mint_s30 &rhs) {
    return norm(lhs.v_) != norm(rhs.v_);
  }
  friend constexpr bool operator<(const mint_s30 &lhs, const mint_s30 &rhs) {
    return lhs.val() < rhs.val();
  }
  friend std::istream &operator>>(std::istream &is, mint_s30 &rhs) {
    i32 x;
    is >> x;
    rhs = mint_s30(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_s30 &rhs) {
    return os << rhs.val();
  }
  friend constexpr u32 abs(mint_s30 const &x) { return x.val(); }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class U, class T = U>
inline vec<T> conv_naive(vec<U> const &l, vec<U> const &r, size_t ans_size) {
  static_assert(sizeof(U) <= sizeof(T));
  size_t n = l.size(), m = r.size();
  vec<T> ans(ans_size);
  if (n < m)
    for (size_t j = 0; j < m; ++j)
      for (size_t i = 0; i < n; ++i) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  else
    for (size_t i = 0; i < n; ++i)
      for (size_t j = 0; j < m; ++j) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  return ans;
}
template <class U, class T = U>
inline vec<T> conv_naive(vec<U> const &l, vec<U> const &r) {
  return conv_naive<U, T>(l, r, l.size() + r.size() - 1);
}
}  // namespace tifa_libs::math
namespace tifa_libs::bit {
template <typename T>
constexpr T bceil(T x) {
  if (x == 0 || x == 1) return 1;
  constexpr int nd = sizeof(T) * 8;
  int sh = nd - cntl0((T)(x - 1u));
  using U = decltype(x << 1);
  if constexpr (!std::is_same_v<U, T>)
    sh |= (sh & nd) << (sizeof(U) / sizeof(T) / 2);
  return (T)1u << sh;
}
}  // namespace tifa_libs::bit
namespace tifa_libs::bit {
template <typename T>
constexpr int cntr0(T x) {
  constexpr int nd = sizeof(T) * 8;
  static_assert(nd <= 128);
  if (x == 0) return nd;
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u) return __builtin_ctz(x);
  else if constexpr (nd <= nd_ul) return __builtin_ctzl(x);
  else if constexpr (nd <= nd_ull) return __builtin_ctzll(x);
  else {
    unsigned long long lo = x & (unsigned long long)(-1);
    if (lo != 0) return __builtin_ctzll(lo);
    unsigned long long hi = x >> nd_ull;
    return __builtin_ctzll(hi) + nd_ull;
  }
}
}  // namespace tifa_libs::bit
namespace tifa_libs::math {
constexpr u32 isqrt(u64 x) {
  if (!x) return 0;
  int c = (bit::bwidth(x) - 1) / 2, sh = 31 - c;
  u32 u = [](u64 x) {
    constexpr uint8_t TAB[192] = {
      128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
      143, 144, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155,
      156, 156, 157, 158, 159, 160, 160, 161, 162, 163, 164, 164, 165, 166, 167,
      167, 168, 169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178,
      179, 179, 180, 181, 181, 182, 183, 183, 184, 185, 186, 186, 187, 188, 188,
      189, 190, 190, 191, 192, 192, 193, 194, 194, 195, 196, 196, 197, 198, 198,
      199, 200, 200, 201, 201, 202, 203, 203, 204, 205, 205, 206, 206, 207, 208,
      208, 209, 210, 210, 211, 211, 212, 213, 213, 214, 214, 215, 216, 216, 217,
      217, 218, 219, 219, 220, 220, 221, 221, 222, 223, 223, 224, 224, 225, 225,
      226, 227, 227, 228, 228, 229, 229, 230, 230, 231, 232, 232, 233, 233, 234,
      234, 235, 235, 236, 237, 237, 238, 238, 239, 239, 240, 240, 241, 241, 242,
      242, 243, 243, 244, 244, 245, 246, 246, 247, 247, 248, 248, 249, 249, 250,
      250, 251, 251, 252, 252, 253, 253, 254, 254, 255, 255, 255};
    u32 u = TAB[(x >> 56) - 64];
    u = (u << 7) + (u32)(x >> 41) / u;
    return (u << 15) + (u32)((x >> 17) / u);
  }(x << 2 * sh);
  u >>= sh;
  u -= (u64)u * u > x;
  return u;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr u64 qpow_mod(u64 a, u64 b, u64 mod) {
  u64 res(1);
  for (a %= mod; b; b >>= 1, a = mul_mod_u(a, a, mod))
    if (b & 1) res = mul_mod_u(res, a, mod);
  return res;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr u32 proot_u32(u32 m) {
  if (m == 2) return 1;
  if (m == 3 || m == 5) return 2;
  if (m == 104857601 || m == 167772161 || m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353 || m == 1004535809) return 3;
  u32 divs[20] = {2};
  u32 cnt = 1, x = (m - 1) / 2;
  x >>= bit::cntr0(x);
  for (u32 i = 3, ed_ = isqrt(x); i <= ed_; i += 2)
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) x /= i;
    }
  if (x > 1) divs[cnt++] = x;
  for (u32 g = 2;; ++g) {
    bool ok = true;
    for (u32 i = 0; i < cnt; ++i)
      if (qpow_mod(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    if (ok) return g;
  }
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint>
struct NTT32 {
  static constexpr u32 MOD = mint::mod();
  static_assert((MOD & 3) == 1, "MOD must be prime with 4k+1");
  NTT32(): root() {}
  size_t size() const { return root.size(); }
  void bzr(size_t len) {
    size_t n = bit::bceil(len);
    assert((MOD - 1) % n == 0);
    if (n == size()) return;
    root.resize(n);
    root[0] = 1;
    mint w = qpow(G, (MOD - 1) / n);
    for (size_t i = 1; i < n; ++i) root[i] = root[i - 1] * w;
  }
  void dif(vec<mint> &f) const {
    size_t n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (size_t i = n / 2, d = 1; i; i /= 2, d *= 2)
      for (size_t j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint u, t;
        for (size_t k = 0; k < i; ++k, w += d) {
          f[j | k] = (u = f[j | k]) + (t = f[i | j | k]);
          f[i | j | k] = (u - t) * (*w);
        }
      }
  }
  void dit(vec<mint> &f) const {
    size_t n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (size_t i = 1, d = n / 2; d; i *= 2, d /= 2)
      for (size_t j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint t;
        for (size_t k = 0; k < i; ++k, w += d) {
          f[i | j | k] = f[j | k] - (t = f[i | j | k] * (*w));
          f[j | k] += t;
        }
      }
    std::reverse(f.begin() + 1, f.end());
    mint t = mint(n).inv();
    for (size_t i = 0; i < n; ++i) f[i] *= t;
  }

private:
  static constexpr mint G = proot_u32(MOD);
  vec<mint> root;
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint>
inline vec<mint> conv_ntt32(vec<mint> l, vec<mint> r, size_t ans_size) {
  static NTT32<mint> ntt;
  ntt.bzr(std::min(l.size() + r.size() - 1, ans_size));
  ntt.dif(l);
  ntt.dif(r);
  for (size_t i = 0; i < ntt.size(); ++i) l[i] *= r[i];
  ntt.dit(l);
  l.resize(ans_size);
  return l;
}
template <class mint>
inline vec<mint> conv_ntt32(vec<mint> const &l, vec<mint> const &r) {
  return conv_ntt32(l, r, l.size() + r.size() - 1);
}
template <class mint, class T = u32>
inline vec<mint> conv_ntt32(vec<T> const &l, vec<T> const &r, size_t ans_size) {
  static_assert(sizeof(T) <= 32);
  vec<mint> l_, r_;
  l_.reserve(l.size());
  r_.reserve(r.size());
  for (auto i : l) l_.push_back(i);
  for (auto i : r) r_.push_back(i);
  return conv_ntt32(l_, r_, ans_size);
}
template <class mint, class T = u32>
inline vec<mint> conv_ntt32(vec<T> const &l, vec<T> const &r) {
  return conv_ntt32<mint, T>(l, r, l.size() + r.size() - 1);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint>
struct polydata_s32 {
  static_assert(mint::mod() > 1 && (mint::mod() & 3) == 1,
                "MOD must be prime with 4k+1");
  using value_type = mint;
  vec<mint> d;
  explicit constexpr polydata_s32(size_t sz = 1): d(sz) {}
  explicit constexpr polydata_s32(std::initializer_list<mint> v): d(v) {}
  explicit constexpr polydata_s32(vec<mint> const &v): d(v) {}
  void conv(polydata_s32 const &r, size_t ans_size) {
    d = ans_size < 32 ? conv_naive(d, r.d, ans_size) :
                        conv_ntt32(d, r.d, ans_size);
  }
  void conv(polydata_s32 const &r) { conv(r, d.size() + r.d.size() - 1); }
};
}  // namespace tifa_libs::math
using mint = tifa_libs::math::mint_s30<167772161>;
using polyd = tifa_libs::math::polydata_s32<mint>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, k;
  std::cin >> n >> k;
  auto ans = tifa_libs::math::stirling1_col_gen<polyd, false>(n, k);
  for (size_t i = 0; i <= n; ++i) std::cout << ans[i] << " \n"[i == n];
  return 0;
}
