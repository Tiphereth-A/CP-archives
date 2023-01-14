#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define TPN typename
#define CR const &
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
template <int ID>
class mint_d31: public mint<mint_d31<ID>, u32> {
  using base = mint<mint_d31<ID>, u32>;
  friend base;
  static inline u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;
  static CEXP u32 norm(i32 x) { return u32(x + (-(x < 0) & (i32)MOD)); }
  static CEXP u32 redc(u64 x) {
    u32 t = u32((x + u64((u32)x * R) * MOD_ODD) >> 32);
    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));
  }
  static CEXP u32 tsf(u32 x) {
    return redc(u64(x % MOD_ODD) * R2) << OFFSET | (x & MASK);
  }

public:
  static CEXP bool FIXED_MOD = false;
  static CEXP void set_mod(u32 m) {
    assert(!(m == 1 || m >> 31));
    for (MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0;
         ++OFFSET, MOD_ODD /= 2);
    MASK = (1_u32 << OFFSET) - 1_u32;
    u32 t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);
    iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv,
      R = iv * (MOD_ODD * iv - t), R2 = u32(-u64(MOD_ODD) % MOD_ODD);
  }
  CEXP mint_d31() {}
  template <int_c T>
  CEXP mint_d31(T v) {
    this->v_ = mod_(v);
  }

private:
  using raw_t = TPN base::raw_type;
  template <int_c T>
  static CEXP raw_t mod_(T v) {
    return tsf(norm(i32(v % (std::conditional_t<sint_c<T>, i32, u32>)mod_())));
  }
  static CEXP raw_t mod_() { return MOD; }
  CEXP raw_t val_() const {
    raw_t h = redc(this->v_ >> OFFSET);
    return ((h - this->v_) * R & MASK) * MOD_ODD + h;
  }
  CEXP raw_t &data_() { return this->v_; }
  CEXP mint_d31 neg_() const {
    mint_d31 res;
    raw_t h = this->v_ >> OFFSET;
    return res.v_ =
             (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-this->v_ & MASK),
           res;
  }
  CEXP mint_d31 &adde_(mint_d31 CR r) {
    raw_t h = (this->v_ >> OFFSET) + (r.v_ >> OFFSET) - MOD_ODD;
    return this->v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) |
                      ((this->v_ + r.v_) & MASK),
           *this;
  }
  CEXP mint_d31 &sube_(mint_d31 CR r) {
    raw_t h = (this->v_ >> OFFSET) - (r.v_ >> OFFSET);
    return this->v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) |
                      ((this->v_ - r.v_) & MASK),
           *this;
  }
  CEXP mint_d31 &mule_(mint_d31 CR r) {
    return this->v_ =
             (redc((u64)(this->v_ >> OFFSET) * (r.v_ >> OFFSET)) << OFFSET) |
             ((this->v_ * r.v_) & MASK),
           *this;
  }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
CEXP u32 isqrt(u64 x) {
  if (!x) return 0;
  const int sh = 31 - i32(std::bit_width(x) - 1) / 2;
  u32 u = [](u64 x) {
    CEXP u8 TAB[192] = {
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
    return u = (u << 7) + (u32)(x >> 41) / u, (u << 15) + (u32)((x >> 17) / u);
  }(x << 2 * sh);
  return u >>= sh, u -= (u64)u * u > x, u;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
CEXP vecu prime_seq(u32 n) {
  vecb sieve(n / 3 + 1, 1);
  for (u32 p = 5, d = 4, i = 1, sqn = isqrt(n); p <= sqn; p += d = 6 - d, ++i) {
    if (!sieve[i]) continue;
    for (u64 q = p * p / 3,
             r = d * p / 3 + (d * p % 3 == 2),
             s = 2 * p,
             qe = sieve.size();
         q < qe;
         q += r = s - r)
      sieve[q] = 0;
  }
  vecu ret{2, 3};
  for (u32 p = 5, d = 4, i = 1; p <= n; p += d = 6 - d, ++i)
    if (sieve[i]) ret.push_back(p);
  while (!ret.empty() && ret.back() > n) ret.pop_back();
  return ret;
}
}  // namespace tifa_libs::math
using mint = tifa_libs::math::mint_d31<-1>;
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  u32 t, r;
  std::cin >> t >> r;
  mint::set_mod(r);
  auto p = tifa_libs::math::prime_seq(10'000'001);
  auto inv = tifa_libs::math::gen_inv<mint>(10'000'001);
  vec<mint> fact(10'000'001);
  fact[0] = 1;
  flt_(u32, i, 1, (u32)fact.size()) fact[i] =
    i == r ? fact[i - 1] : fact[i - 1] * i;
  vec<mint> ppn1(p.size()), ppinv(p.size());
  ppn1[0] = 1;
  flt_(u32, i, 1, (u32)p.size()) ppn1[i] = ppn1[i - 1] * (p[i] - 1);
  flt_(u32, i, 0, (u32)p.size()) if (ppinv[i] = i ? ppinv[i - 1] : 1; r != p[i])
    ppinv[i] *= inv[p[i]];
  vecu pos(10'000'001);
  pos[0] = pos[1] = -1_u32;
  u32 _ = 0;
  flt_(u32, i, 2, (u32)pos.size()) {
    pos[i] = pos[i - 1];
    if (_ < p.size() && i == p[_]) ++pos[i], ++_;
  }
  while (t--) {
    u32 n, m;
    std::cin >> n >> m;
    if (n >= r && m < r) {
      std::cout << "0\n";
      continue;
    }
    std::cout << fact[n] * (~pos[m] ? ppn1[pos[m]] * ppinv[pos[m]] : 1) << '\n';
  }
  return 0;
}
