#include <bits/stdc++.h>
#define CEXP constexpr
#define TPN typename
#define CR const &
#define cT_(...)                                            \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t), \
                     __VA_ARGS__,                           \
                     __VA_ARGS__ CR>
#define fle_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; ++i)
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
template <class T>
using ptt = std::pair<T, T>;
template <class T>
using pt3 = std::tuple<T, T, T>;
template <class T>
using pt4 = std::tuple<T, T, T, T>;
template <class E>
using itl = std::initializer_list<E>;
template <class T, usz N>
using arr = std::array<T, N>;
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
using strn = std::string;
template <class T, usz ext = std::dynamic_extent>
using spn = std::span<T const, ext>;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                              \
  mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T) mk_(vec, A, T) mk_(vvec, A, T) \
    mk_(v3ec, A, T) mk_(vecpt, A, T) mk_(vvecpt, A, T) mk_(ptvec, A, T)       \
      mk_(ptvvec, A, T) mk_(spn, A, T) mk_(itl, A, T)
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
namespace tifa_libs::math {
template <class T, u32 N>
struct conv_subset {
  using arr_t = arr<T, N + 1>;
  vecu pc;
  CEXP void add(arr_t &l, cT_(arr_t) r, u32 d) const {
    flt_(u32, i, 0, d) l[i] += r[i];
  }
  CEXP void sub(arr_t &l, cT_(arr_t) r, u32 d) const {
    fle_(u32, i, d, N) l[i] -= r[i];
  }

public:
  explicit CEXP conv_subset(): pc(1u << N) {
    for (u32 i = 1; i < (1u << N); ++i) pc[i] = pc[i - (i & -i)] + 1;
  }
  CEXP void zeta(vec<arr_t> &a) const {
    for (u32 w = 1; w < (u32)a.size(); w *= 2)
      for (u32 k = 0; k < (u32)a.size(); k += w * 2)
        flt_(u32, i, 0, w) add(a[k + w + i], a[k + i], pc[k + w + i]);
  }
  CEXP void mobius(vec<arr_t> &a) const {
    const u32 n = (u32)a.size();
    for (u32 w = n >> 1; w; w /= 2)
      for (u32 k = 0; k < n; k += w * 2)
        flt_(u32, i, 0, w) sub(a[k + w + i], a[k + i], pc[k + w + i]);
  }
  CEXP vec<arr_t> lift(spn<T> a) const {
    vec<arr_t> A(a.size());
    flt_(u32, i, 0, (u32)a.size()) std::ranges::fill(A[i], T()),
      A[i][pc[i]] = a[i];
    return A;
  }
  CEXP vec<T> unlift(spn<arr_t> A) const {
    vec<T> a(A.size());
    flt_(u32, i, 0, (u32)A.size()) a[i] = A[i][pc[i]];
    return a;
  }
  CEXP void prod(vec<arr_t> &A, spn<arr_t> B) const {
    u32 n = (u32)A.size(), d = (u32)std::countr_zero(n);
    flt_(u32, i, 0, n) {
      arr_t c;
      fle_(u32, j, 0, d) for (u32 k = 0; k <= d - j; ++k) c[j + k] +=
        A[i][j] * B[i][k];
      A[i].swap(c);
    }
  }
  CEXP vec<T> conv(spn<T> a, spn<T> b) const {
    vec<arr_t> A = lift(a), B = lift(b);
    return zeta(A), zeta(B), prod(A, B), mobius(A), unlift(A);
  }
};
}  // namespace tifa_libs::math
namespace tifa_libs {
CEXP u32 u32tostr_si16(u64 x, char *s) {
  if (x <= 9) return *s = (char)(x | 0x30), 1;
  else if (x <= 99) {
    u64 lo = x, ll = ((lo * 103) >> 9) & 0x1E;
    return lo += ll * 3, ll = ((lo & 0xF0) >> 4) | ((lo & 0x0F) << 8),
                         *(u16 *)s = (u16)(ll | 0x3030), 2;
  } else return 0;
}
CEXP u32 u32tostr_si32(u64 x, char *s) {
  u64 lo = 0, ll = 0;
  u32 digits = 0;
  if (x <= 99) return u32tostr_si16(x, s);
  lo = x, digits = (lo > 999) ? 4 : 3;
  ll = ((lo * 5243) >> 19) & 0xFF, lo = ((lo - ll * 100) << 16) | ll,
  ll = ((lo * 103) >> 9) & 0x1E001E, lo += ll * 3;
  ll =
    ((lo & 0x00F000F0) << 28) | ((lo & 0x000F000F) << 40) | 0x3030303000000000;
  if (u8 *p = (u8 *)&ll; digits == 4) *(u32 *)s = *(u32 *)(&p[4]);
  else *(u16 *)s = *(u16 *)(&p[5]), *(((u8 *)s) + 2) = p[7];
  return digits;
}
CEXP u32 u32tostr(u64 x, char *s) {
  u64 low = 0, ll = 0;
  u32 digits = 0;
  if (x <= 9999) return u32tostr_si32(x, s);
  if (x < 100000000) {
    if ((low = x) > 999999) digits = (low > 9999999) ? 8 : 7;
    else digits = (low > 99999) ? 6 : 5;
  } else {
    u64 high = (x * 0x55E63B89) >> 57;
    low = x - (high * 100000000), digits = u32tostr_si16(high, s) + 8;
  }
  ll = (low * 109951163) >> 40, (low -= ll * 10000) |= ll << 32;
  ll = ((low * 5243) >> 19) & 0x000000FF000000FF,
  low = ((low - ll * 100) << 16) | ll;
  ll = ((low * 103) >> 9) & 0x001E001E001E001E, low += ll * 3;
  ll = ((low & 0x00F000F000F000F0) >> 4) | (low & 0x000F000F000F000F) << 8;
  ll = (ll >> 32) | (ll << 32) | 0x3030303030303030;
  if (digits >= 8) memcpy(s + digits - 8, &ll, 8);
  else {
    u32 d = digits;
    char *s1 = s, *pll = &(((char *)&ll)[8 - digits]);
    if (d >= 4) memcpy(s1, pll, 4), s1 += 4, pll += 4, d -= 4;
    if (d >= 2) memcpy(s1, pll, 2), s1 += 2, pll += 2, d -= 2;
    if (d > 0) *(u8 *)s1 = *(u8 *)pll;
  }
  return digits;
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
namespace tifa_libs {
namespace fastio_impl_ {
template <u32 BUF>
class fastin {
  char bf_[BUF], *now_ = bf_, *end_ = bf_;
  FILE *f_;

public:
  explicit fastin(FILE *f = stdin): f_(f) {}
  char get() {
    return now_ == end_ &&
               (end_ = (now_ = bf_) + fread(bf_, 1, BUF, f_), now_ == end_) ?
             EOF :
             *(now_)++;
  }
  char peek() {
    return now_ == end_ &&
               (end_ = (now_ = bf_) + fread(bf_, 1, BUF, f_), now_ == end_) ?
             EOF :
             *(now_);
  }
  void rebind(FILE *f) { f_ = f, now_ = end_ = bf_; }
  bool iseof() { return peek() == EOF; }
  template <class T>
  requires(sint_c<T> && !char_c<T>)
  fastin &read(T &n) {
    bool is_neg = false;
    char ch = get();
    while (!isdigit(ch)) is_neg |= ch == '-', ch = get();
    n = 0;
    while (isdigit(ch)) (n *= 10) += ch & 15, ch = get();
    if (is_neg) n = -n;
    return *this;
  }
  template <class T>
  requires(uint_c<T> && !char_c<T>)
  fastin &read(T &n) {
    char ch = get();
    while (!isdigit(ch)) ch = get();
    n = 0;
    while (isdigit(ch)) (n *= 10) += ch & 15, ch = get();
    return *this;
  }
  template <mint_c T>
  fastin &read(T &n) {
    decltype(std::declval<T>().sval()) x;
    return read(x), n = T(x), *this;
  }
  template <char_c T>
  fastin &read(T &n) {
    while (!isgraph(n = get()));
    return *this;
  }
  fastin &read(char *n) {
    char *n_ = n;
    while (!isgraph(*n_ = get()));
    while (isgraph(*(++n_) = get()));
    return *n_ = '\0', *this;
  }
  fastin &read(strn &n) {
    n.clear();
    char n_;
    while (!isgraph(n_ = get()));
    n.push_back(n_);
    while (isgraph(n_ = get())) n.push_back(n_);
    return *this;
  }
  template <class T, class U>
  fastin &read(std::pair<T, U> &p) {
    return read(p.first).read(p.second);
  }
  template <class... Ts>
  fastin &read(std::tuple<Ts...> &p) {
    return std::apply([&](Ts &...targs) { ((read(targs)), ...); }, p), *this;
  }
  template <container_c T>
  fastin &read(T &p) {
    if (p.begin() == p.end()) return *this;
    for (auto &i : p) read(i);
    return *this;
  }
  fastin &getline(char *n) {
    char *n_ = n;
    while (!isprint(*n_ = get()));
    while (isprint(*(++n_) = get()));
    return *n_ = '\0', *this;
  }
  fastin &getline(strn &n) {
    char n_;
    while (!isprint(n_ = get()));
    n.push_back(n_);
    while (isprint(n_ = get())) n.push_back(n_);
    return *this;
  }
  template <char_c T>
  fastin &strict_read(T &n) {
    return n = get(), *this;
  }
  template <class T>
  fastin &operator>>(T &val) {
    return read(val);
  }
};
template <u32 BUF, u32 INTBUF>
class fastout {
  char int_bf_[INTBUF], *now_ib_ = int_bf_;
  FILE *f_;
  char *now_, bf_[BUF];
  const char * const end_ = bf_ + BUF;

public:
  explicit fastout(FILE *file = stdout): f_(file), now_(bf_) {}
  fastout &operator=(fastout CR r) {
    if (&r == this) return *this;
    return f_ = r.f_, now_ = bf_ + (r.now_ - r.bf_),
           memcpy(bf_, r.bf_, sizeof(*bf_) * (r.now_ - r.bf_)), *this;
  }
  fastout(fastout CR r) { *this = r; }
  ~fastout() { flush(); }
  void flush() { fwrite(bf_, 1, usz(now_ - bf_), f_), now_ = bf_; }
  void rebind(FILE *file) { f_ = file; }
  template <char_c T>
  fastout &write(T n) {
    if (now_ == end_) flush();
    return *(now_++) = n, *this;
  }
  fastout &write(const char *n) {
    usz len = strlen(n), l_;
    const char *n_ = n;
    while (now_ + len >= end_)
      memcpy(now_, n_, l_ = usz(end_ - now_)), now_ += l_, n_ += l_, len -= l_,
        flush();
    return memcpy(now_, n_, len), now_ += len, *this;
  }
  template <class T>
  requires(sint_c<T> && !char_c<T>)
  fastout &write(T n) {
    if (n < 0) write('-'), n = -n;
    return write(to_uint_t<T>(n));
  }
  template <class T>
  requires(uint_c<T> && !char_c<T>)
  fastout &write(T n) {
    if CEXP (sizeof(T) <= 4)
      return memset(now_ib_ = int_bf_, 0, 11), u32tostr(n, now_ib_),
             write(now_ib_);
    now_ib_ = int_bf_ + INTBUF - 1;
    do *(--(now_ib_)) = char(n % 10) | '0';
    while (n /= 10);
    return write(now_ib_);
  }
  template <mint_c T>
  fastout &write(T n) {
    return write(n.val());
  }
  fastout &write(strn CR str) { return write(str.c_str()); }
  template <class T, class U>
  fastout &write(std::pair<T, U> CR p) {
    return write(p.first).space().write(p.second);
  }
  template <class... Ts>
  fastout &write(std::tuple<Ts...> CR p) {
    std::apply(
      [&](Ts CR... targs) {
        usz n{0};
        ((write(targs).space_if(++n != sizeof...(Ts))), ...);
      },
      p);
    return *this;
  }
  template <container_c T>
  fastout &write(T CR p) {
    if (p.begin() == p.end()) return *this;
    auto it = p.begin();
    for (write(*it++); it != p.end(); ++it) space().write(*it);
    return *this;
  }
  fastout &linebreak() { return write('\n'); }
  fastout &linebreak_if(bool flag) { return flag ? linebreak() : *this; }
  fastout &space() { return write(' '); }
  fastout &space_if(bool flag) { return flag ? space() : *this; }
  template <class T>
  fastout &operator<<(T CR val) {
    return write(val);
  }
};
}  // namespace fastio_impl_
inline fastio_impl_::fastin<0x200005> fin;
inline fastio_impl_::fastout<0x200005, 41> fout;
}  // namespace tifa_libs
CEXP u32 MOD = 1e9 + 9;
namespace tifa_libs::math {
template <sint_c T>
CEXP T safe_mod(T x, to_uint_t<T> mod) {
  return ((x %= (T)mod) < 0 ? x + (T)mod : x);
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
  explicit CEXP operator T() const {
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
using mint = tifa_libs::math::mint_s30<MOD>;
int main() {
  u32 n;
  tifa_libs::fin >> n;
  vec<mint> a(1 << n), b(1 << n);
  for (auto &i : a) tifa_libs::fin >> i;
  for (auto &i : b) tifa_libs::fin >> i;
  tifa_libs::math::conv_subset<mint, 20> cvs;
  tifa_libs::fout << cvs.conv(a, b) << '\n';
  return 0;
}
