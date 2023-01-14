#include <bits/stdc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
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
using strn = std::string;
using strnv = std::string_view;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
struct edge_t {
  T w;
  u32 u, v;
  CEXP auto operator<=>(edge_t CR) const = default;
};
template <class T>
struct pt3 {
  T _0, _1, _2;
  CEXP auto operator<=>(pt3 CR) const = default;
};
template <class T>
struct pt4 {
  T _0, _1, _2, _3;
  CEXP auto operator<=>(pt4 CR) const = default;
};
template <class E>
using itl = std::initializer_list<E>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using v3ec = vec<vvec<T>>;
template <class T>
using vecpt = vec<ptt<T>>;
template <class T>
using vvecpt = vvec<ptt<T>>;
template <class T>
using ptvec = ptt<vec<T>>;
template <class T>
using ptvvec = ptt<vvec<T>>;
template <class T, usz ext = std::dynamic_extent>
using spn = std::span<T const, ext>;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                          \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)          \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T)       \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) \
        mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
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
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
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
  iterable_c<T> && !std::same_as<std::remove_cvref_t<T>, strn> &&
  !std::same_as<std::remove_cvref_t<T>, strnv>;
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
using to_sint_t = TPN to_sint<T>::type;
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
template <class T>
using to_uint_t = TPN to_uint<T>::type;
}  // namespace tifa_libs
namespace tifa_libs::math {
template <sint_c T>
CEXP T safe_mod(T x, to_uint_t<T> mod) {
  return ((x %= (T)mod) < 0 ? x + (T)mod : x);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
CEXP i64 mul_mod_s(i64 a, i64 b, u64 mod) {
  if (std::bit_width((u64)abs(a)) + std::bit_width((u64)abs(b)) < 64)
    return safe_mod(a * b % (i64)mod, mod);
  return safe_mod((i64)((i128)a * b % mod), mod);
}
CEXP u64 mul_mod_u(u64 a, u64 b, u64 mod) {
  if (std::bit_width(a) + std::bit_width(b) <= 64) return a * b % mod;
  return (u64)((u128)a * b % mod);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
CEXP vecuu gen_fact(u32 n, u64 mod) {
  if (n <= 1) return vecuu(n, 1);
  vecuu ans(n);
  ans[0] = ans[1] = 1;
  flt_(u32, i, 2, n) ans[i] = mul_mod_u(ans[i - 1], i, mod);
  return ans;
}
template <class mint>
CEXP vec<mint> gen_fact(u32 n) {
  vec<mint> ans(n);
  auto _ = gen_fact(n, mint::mod());
  flt_(u32, i, 0, n) ans[i] = _[i];
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
CEXP vecuu gen_inv(u32 n, u64 mod) {
  if (n <= 1) return vecuu(n, 1);
  vecuu ans(n);
  ans[0] = ans[1] = 1;
  flt_(u32, i, 2, n) ans[i] = mul_mod_u(mod - mod / i, ans[mod % i], mod);
  return ans;
}
template <class mint>
CEXP vec<mint> gen_inv(u32 n) {
  vec<mint> ans(n);
  auto _ = gen_inv(n, mint::mod());
  flt_(u32, i, 0, n) ans[i] = _[i];
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
CEXP vecuu gen_ifact(u32 n, u64 mod, vecuu inv) {
  flt_(u32, i, 2, n) inv[i] = mul_mod_u(inv[i], inv[i - 1], mod);
  return inv;
}
CEXP vecuu gen_ifact(u32 n, u64 mod) {
  return gen_ifact(n, mod, gen_inv(n, mod));
}
template <class mint>
CEXP vec<mint> gen_ifact(u32 n, vec<mint> inv) {
  flt_(u32, i, 2, n) inv[i] *= inv[i - 1];
  return inv;
}
template <class mint>
CEXP vec<mint> gen_ifact(u32 n) {
  return gen_ifact(n, gen_inv<mint>(n));
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint>
struct Binom {
  vec<mint> fact, ifact;
  static CEXP u64 mod() { return mint::mod(); }
  CEXPE Binom(u32 max_m = 0)
    : fact(gen_fact<mint>(std::min((u32)mod(), max_m + 1))),
      ifact(gen_ifact<mint>(std::min((u32)mod(), max_m + 1))) {}
  template <uint_c T>
  CEXP mint mCn(T m, T n) const {
    return m < n ? 0 : mPn(m, n) * ifact[(usz)n];
  }
  template <sint_c T>
  CEXP mint mCn(T m, T n) const {
    return m < n || n < 0 ? 0 : mCn(to_uint_t<T>(m), to_uint_t<T>(n));
  }
  template <int_c T>
  CEXP mint lucas(T m, T n) const {
    assert(mint::mod() > 1);
    auto f = [this](auto &&f, auto m, auto n) -> mint {
      return n == 0 ?
               1 :
               this->mCn(m % mod(), n % mod()) * f(f, m / mod(), n / mod());
    };
    return m < n || n < 0 ? 0 : f(f, to_uint_t<T>(m), to_uint_t<T>(n));
  }
  template <uint_c T>
  CEXP mint mPn(T m, T n) const {
    return m < n ? 0 : fact[(usz)m] * ifact[(usz)(m - n)];
  }
  template <sint_c T>
  CEXP mint mPn(T m, T n) const {
    return m < n || n < 0 ? 0 : mPn(to_uint_t<T>(m), to_uint_t<T>(n));
  }
  template <uint_c T>
  CEXP mint mHn(T m, T n) const {
    return n <= 0 ? n == 0 : mCn(m + n - 1, n);
  }
  template <sint_c T>
  CEXP mint mHn(T m, T n) const {
    return m < 0 || n <= 0 ? n == 0 : mHn(to_uint_t<T>(m), to_uint_t<T>(n));
  }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <uint_c U, bool only_x = false>
CEXP auto exgcd_b(U a, U b) {
  using T = to_sint_t<U>;
  if CEXP (only_x) {
    if (!a) return std::make_tuple(b, (T)0);
    if (!b) return std::make_tuple(a, (T)1);
  } else {
    if (!a) return std::make_tuple(b, (T)0, (T) !!b);
    if (!b) return std::make_tuple(a, (T)1, (T)0);
  }
  auto r = std::__countr_zero(a | b);
  a >>= r, b >>= r;
  T x = (T)a, y = (T)b, s = 1, t = 0, u = 0, v = 1;
  while (x) {
    while (!(x & 1))
      if (x /= 2; !((s | t) & 1)) s /= 2, t /= 2;
      else s = (s + (T)b) / 2, t = (t - (T)a) / 2;
    while (!(y & 1))
      if (y /= 2; !((u | v) & 1)) u /= 2, v /= 2;
      else u = (u + (T)b) / 2, v = (v - (T)a) / 2;
    if (x >= y) x -= y, s -= u, t -= v;
    else y -= x, u -= s, v -= t;
  }
  if (y > 1) a /= (U)y, b /= (U)y;
  if (a && (U)abs(v) >= a) {
    const T _ = v / (T)a;
    v -= _ * (T)a, u += _ * (T)b;
  }
  if (b && (U)abs(u) >= b) {
    const T _ = u / (T)b;
    u -= _ * (T)b, v += _ * (T)a;
  }
  if (T u_ = u + (T)b, v_ = v - (T)a; abs(u_) + abs(v_) <= abs(u) + abs(v))
    u = u_, v = v_;
  if (T u_ = u - (T)b, v_ = v + (T)a; abs(u_) + abs(v_) <= abs(u) + abs(v))
    u = u_, v = v_;
  if CEXP (only_x) return std::make_tuple(U(y << r), u);
  else return std::make_tuple(U(y << r), u, v);
}
template <sint_c T, bool only_x = false>
CEXP auto exgcd(T a, T b) {
  using U = to_uint_t<T>;
  if (auto [x, y] = std::minmax(a, b); x >= 0 && y <= T(U(-1) >> sizeof(U)))
    return exgcd_b<U, only_x>((U)a, (U)b);
  if CEXP (only_x) {
    T s = 1, u = 0;
    while (b) {
      T c = a / b;
      std::tie(s, u, a, b) = std::make_tuple(u, s - u * c, b, a - b * c);
    }
    return std::make_tuple((U)a, s);
  } else {
    T s = 1, t = 0, u = 0, v = 1;
    while (b) {
      T c = a / b;
      std::tie(s, t, u, v, a, b) =
        std::make_tuple(u, v, s - u * c, t - v * c, b, a - b * c);
    }
    return std::make_tuple((U)a, s, t);
  }
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <uint_c T>
CEXP ptt<T> inv_gcd(T n, T mod) {
  using U = to_sint_t<T>;
  auto [g, x] = exgcd<U, true>(U(n % mod), (U)mod);
  return {g, safe_mod(x, mod)};
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <uint_c T, uint_c U>
CEXP U inverse(T n, U mod) {
  auto [g, x] = inv_gcd(U(n % mod), mod);
  assert(g == 1);
  return x;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class D, uint_c Rt>
class mint {
  CEXP D CR d() const { return static_cast<D CR>(*this); }
  CEXP D &d() { return static_cast<D &>(*this); }

protected:
  Rt v_{};

public:
  CEXP mint() {}
  template <int_c T>
  CEXP mint(T v): v_(D::mod_(v)) {}
  CEXP operator D() { return d(); }
  using raw_type = Rt;
  using sraw_type = to_sint_t<Rt>;
  static CEXP raw_type mod() { return D::mod_(); }
  static CEXP sraw_type smod() { return (sraw_type)D::mod_(); }
  CEXP raw_type val() const { return d().val_(); }
  CEXP sraw_type sval() const { return (sraw_type)d().val_(); }
  CEXP raw_type &data() { return d().data_(); }
  template <int_c T>
  CEXPE operator T() const {
    return (T)val();
  }
  CEXP mint &operator+=(mint CR r) { return d().adde_(r.d()); }
  CEXP mint &operator-=(mint CR r) { return d().sube_(r.d()); }
  CEXP mint &operator*=(mint CR r) { return d().mule_(r.d()); }
  CEXP mint &operator/=(mint CR r) { return *this = *this * r.inv(); }
  CEXP mint CR operator+() const { return *this; }
  CEXP mint operator-() const { return d().neg_(); }
  CEXP mint inv() const { return inverse(val(), mod()); }
  friend CEXP mint operator+(mint l, mint CR r) { return l += r; }
  friend CEXP mint operator-(mint l, mint CR r) { return l -= r; }
  friend CEXP mint operator*(mint l, mint CR r) { return l *= r; }
  friend CEXP mint operator/(mint l, mint CR r) { return l /= r; }
  friend CEXP bool operator==(mint CR l, mint CR r) {
    return l.val() == r.val();
  }
  friend CEXP auto operator<=>(mint CR l, mint CR r) {
    return l.sval() - r.sval();
  }
  friend std::istream &operator>>(std::istream &is, mint &x) {
    i64 _;
    return is >> _, x = mint(_), is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint CR x) {
    return os << x.val();
  }
  friend CEXP mint abs(mint CR x) { return x.val(); }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <u32 MOD>
class mint_s30: public mint<mint_s30<MOD>, u32> {
  using base = mint<mint_s30<MOD>, u32>;
  friend base;
  static CEXP u32 MOD2 = MOD << 1;
  static CEXP u32 R = []() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    return iv *= t - MOD * iv, iv *= t - MOD * iv, iv * (MOD * iv - t);
  }();
  static CEXP u32 R2 = -(u64)(MOD) % MOD;
  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);
  static CEXP u32 reduce(u64 x) {
    return u32((x + u64((u32)x * R) * MOD) >> 32);
  }
  static CEXP u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }

public:
  static CEXP bool FIXED_MOD = true;
  CEXP mint_s30() {}
  template <int_c T>
  CEXP mint_s30(T v) {
    this->v_ = mod_(v);
  }

private:
  using raw_t = TPN base::raw_type;
  template <sint_c T>
  static CEXP raw_t mod_(T v) {
    return reduce(u64(v % (i32)mod_() + (i32)mod_()) * R2);
  }
  template <uint_c T>
  static CEXP raw_t mod_(T v) {
    return reduce(u64(v % mod_()) * R2);
  }
  static CEXP raw_t mod_() { return MOD; }
  CEXP raw_t val_() const { return norm(reduce(this->v_)); }
  CEXP raw_t &data_() { return this->v_; }
  CEXP mint_s30 neg_() const {
    mint_s30 res;
    return res.v_ = (MOD2 & -(this->v_ != 0)) - this->v_, res;
  }
  CEXP mint_s30 &adde_(mint_s30 CR r) {
    return this->v_ += r.v_ - MOD2, this->v_ += MOD2 & -(this->v_ >> 31), *this;
  }
  CEXP mint_s30 &sube_(mint_s30 CR r) {
    return this->v_ -= r.v_, this->v_ += MOD2 & -(this->v_ >> 31), *this;
  }
  CEXP mint_s30 &mule_(mint_s30 CR r) {
    return this->v_ = reduce(u64(this->v_) * r.v_), *this;
  }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
CEXP T qpow(T a, u64 b, cT_(T) init_v = T{1}) {
  T res = init_v;
  for (; b; b >>= 1, a = a * a)
    if (b & 1) res = res * a;
  return res;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
class rpow {
  vecuu b0, b1;
  u64 b_, m_;

public:
  CEXPE rpow(): b0(65536), b1(65536), b_(), m_() {}
  CEXP rpow(u64 base_, u32 mod_): rpow() { reset(base_, mod_); }
  CEXP void reset(u64 base, u32 mod) {
    if (b_ == base % mod && m_ == mod) return;
    b_ = base % mod, m_ = mod, b0[0] = b1[0] = 1;
    flt_(u32, i, 1, 65536) b0[i] = mul_mod_u(b0[i - 1], b_, m_);
    u64 _(mul_mod_u(b0.back(), b_, m_));
    flt_(u32, i, 1, 65536) b1[i] = mul_mod_u(b1[i - 1], _, m_);
  }
  CEXP void swap(rpow &r) {
    b0.swap(r.b0), b1.swap(r.b1);
    ::tifa_libs::swap(b_, r.b_), ::tifa_libs::swap(m_, r.m_);
  }
  CEXP u64 base() const { return b_; }
  CEXP u64 mod() const { return m_; }
  CEXP u64 operator()(u32 x) const {
    return mul_mod_u(b0[x & 65535], b1[x >> 16], m_);
  }
};
}  // namespace tifa_libs::math
constexpr u32 MOD = 998244353;
using mint = tifa_libs::math::mint_s30<MOD>;
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  tifa_libs::math::rpow rp3(3, MOD);
  tifa_libs::math::Binom<mint> binom(n);
  mint ans1 = 0, ans2 = 0;
  for (u32 i = 1; i <= n; ++i)
    if (mint _ = binom.mCn(n, i) *
                 tifa_libs::math::qpow(mint(3), (u64)n * (n - i) + i);
        i & 1)
      ans1 += _;
    else ans1 -= _;
  for (u32 i = 0; i < n; ++i)
    if (mint _0 = MOD - rp3(i),
        _ = binom.mCn(n, i) *
            (tifa_libs::math::qpow(1 + _0, n) - tifa_libs::math::qpow(_0, n));
        i & 1)
      ans2 += _;
    else ans2 -= _;
  std::cout << ans1 * 2 + ans2 * 3 << '\n';
  return 0;
}
