#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
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
template <class U, class T>
using vecp = vec<std::pair<U, T>>;
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
namespace tifa_libs {
namespace fastio_impl_ {
template <u32 BUF>
class fastin {
  char bf_[BUF], *now_ = bf_, *end_ = bf_;
  FILE *f_;

public:
  fastin(FILE *f = stdin): f_(f) {}
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
  fastout(FILE *file = stdout): f_(file), now_(bf_) {}
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
    return std::apply(
             [&](Ts CR... targs) {
               usz n{0};
               ((write(targs).space_if(++n != sizeof...(Ts))), ...);
             },
             p),
           *this;
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
namespace tifa_libs::math {
enum ccore_t { ct_FFT, ct_3NTT, ct_NTT };
template <class mint, class ccore>
requires requires(ccore cc, vec<mint> l, vec<mint> r, u32 sz) {
  { ccore::ct_cat } -> std::same_as<ccore_t CR>;
  cc.conv(l, r);
  cc.conv(l, r, sz);
}
class poly {
  vec<mint> d;

public:
  using value_type = mint;
  using data_type = vec<value_type>;
  using ccore_type = ccore;
  static inline ccore_type conv_core;
  CEXPE poly(u32 sz = 1, cT_(value_type) val = value_type{}): d(sz, val) {}
  CEXP poly(TPN data_type::const_iterator begin,
            TPN data_type::const_iterator end)
    : d(begin, end) {}
  CEXP poly(itl<value_type> v): d(v) {}
  CEXP poly(spn<value_type> v): d(v.begin(), v.end()) {}
  friend CEXP std::istream &operator>>(std::istream &is, poly &poly) {
    for (auto &val : poly.d) is >> val;
    return is;
  }
  friend CEXP std::ostream &operator<<(std::ostream &os, poly CR poly) {
    if (!poly.size()) return os;
    flt_(u32, i, 1, (u32)poly.size()) os << poly[i - 1] << ' ';
    return os << poly.d.back();
  }
  CEXP u32 size() const { return (u32)d.size(); }
  CEXP bool empty() const {
    for (auto &&i : d)
      if (i != 0) return 0;
    return 1;
  }
  CEXP data_type &data() { return d; }
  CEXP data_type CR data() const { return d; }
  CEXP value_type &operator[](u32 x) { return d[x]; }
  CEXP value_type CR operator[](u32 x) const { return d[x]; }
  CEXP value_type operator()(value_type x) const {
    value_type ans = 0;
    for (u32 i = size() - 1; ~i; --i) ans = ans * x + d[i];
    return ans;
  }
  template <class F>
  requires requires(F f, u32 idx, mint &val) { f(idx, val); }
  CEXP void apply_range(u32 l, u32 r, F &&f) {
    assert(l < r && r <= size());
    flt_(u32, i, l, r) f(i, d[i]);
  }
  template <class F>
  CEXP void apply(F &&f) {
    apply_range(0, size(), std::forward<F>(f));
  }
  CEXP void resize(u32 size) { d.resize(size); }
  CEXP poly pre(u32 size) const {
    poly _ = *this;
    return _.resize(size), _;
  }
  CEXP void strip() {
    auto it = std::find_if(
      d.rbegin(), d.rend(), [](cT_(mint) x) { return x.val() != 0; });
    if (d.resize(usz(d.rend() - it)); d.empty()) d.push_back(value_type(0));
  }
  friend poly stripped(poly p) { return p.strip(), p; }
  CEXP void reverse(u32 n = 0) {
    std::reverse(d.begin(), d.begin() + (n ? n : size()));
  }
  CEXP void conv(poly CR r, u32 ans_size = 0) {
    conv_core.conv(d, r.d, ans_size);
  }
  CEXP poly operator-() const {
    poly ret = *this;
    return ret.apply([](u32, auto &v) { v = -v; }), ret;
  }
  friend CEXP poly operator+(poly p, value_type c) { return p[0] += c, p; }
  friend CEXP poly operator+(value_type c, poly CR p) { return p + c; }
  friend CEXP poly operator-(poly p, value_type c) { return p[0] -= c, p; }
  friend CEXP poly operator-(value_type c, poly CR p) { return p - c; }
  CEXP poly &operator*=(value_type c) {
    return apply([&c](u32, auto &v) { v *= c; }), *this;
  }
  friend CEXP poly operator*(poly p, value_type c) { return p *= c; }
  friend CEXP poly operator*(value_type c, poly p) { return p *= c; }
  CEXP poly &operator+=(poly CR r) {
    if (!r.size()) return *this;
    resize(max(size(), r.size())),
      apply_range(0, r.size(), [&r](u32 i, auto &v) { v += r[i]; });
    return *this;
  }
  friend CEXP poly operator+(poly l, poly CR r) { return l += r; }
  CEXP poly &operator-=(poly CR r) {
    if (!r.size()) return *this;
    return resize(max(size(), r.size())),
           apply_range(0, r.size(), [&r](u32 i, auto &v) { v -= r[i]; }), *this;
  }
  friend CEXP poly operator-(poly l, poly CR r) { return l -= r; }
  CEXP poly &operator*=(poly CR r) {
    if (!r.size()) return resize(1), d[0] = 0, *this;
    return conv(r), *this;
  }
  friend CEXP poly operator*(poly l, poly CR r) { return l *= r; }
  CEXP auto operator<=>(poly CR r) const {
    return stripped(*this).d <=> stripped(r).d;
  }
  CEXP bool operator==(poly CR r) const {
    return stripped(*this).d == stripped(r).d;
  }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint, class ccore>
CEXP poly<mint, ccore> inv_fps(poly<mint, ccore> CR p, u32 n = 0) {
  assert(p[0] != 0);
  if (!n) n = p.size();
  poly<mint, ccore> a{p[0].inv()};
  for (u32 i = 1; i < n; i *= 2)
    a = (a * 2 - (a * a * p).pre(i * 2)).pre(i * 2);
  return a.pre(n);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint, class ccore>
CEXP poly<mint, ccore> comp_fps(poly<mint, ccore> f, poly<mint, ccore> g) {
  using poly_t = poly<mint, ccore>;
  ccore core2, core4;
  auto dfs = [&](auto &&dfs, vec<mint> b, u32 n, u32 h, u32 k) -> vec<mint> {
    if (!n) {
      poly_t _{b.begin(), b.begin() + k};
      _.data().push_back(1), _.reverse(), (_ = inv_fps(_)).reverse();
      poly_t g_ = f * _;
      vec<mint> a(k * h);
      flt_(u32, i, 0, (u32)f.size()) a[k - i - 1] = g_[i + k];
      return a;
    }
    vec<mint> bb(k * h * 4), cc(k * h * 2);
    flt_(u32, i, 0, k) std::copy(
      b.begin() + i * h, b.begin() + i * h + n + 1, bb.begin() + i * h * 2);
    bb[k * h * 2] += 1, core4.dif(bb);
    for (u32 i = 0; i < k * h * 4; i += 2) swap(bb[i], bb[i + 1]);
    flt_(u32, i, 0, k * h * 2) cc[i] = bb[i * 2] * bb[i * 2 + 1];
    core2.dit(cc), cc[0] -= 1, b.assign(k * h, 0);
    flt_(u32, i, 0, k * 2) fle_(u32, j, 0, n / 2) b[i * h / 2 + j] =
      cc[i * h + j];
    vec<mint> a = dfs(dfs, b, n / 2, h / 2, k * 2), aa(k * h * 4);
    flt_(u32, i, 0, k * 2) fle_(u32, j, 0, n / 2) aa[(i * h + j) * 2 + n % 2] =
      a[i * h / 2 + j];
    core4.dif(aa);
    for (u32 i = 1; i < k * h * 4; i *= 2)
      std::reverse(bb.begin() + i, bb.begin() + i * 2);
    flt_(u32, i, 0, k * h * 4) aa[i] *= bb[i];
    core4.dit(aa), a.assign(k * h, 0);
    flt_(u32, i, 0, k) std::copy(aa.begin() + i * h * 2,
                                 aa.begin() + i * h * 2 + n + 1,
                                 a.begin() + i * h);
    return a;
  };
  const u32 n = max(g.size(), f.size()), h = std::bit_ceil(n);
  poly_t b(h);
  auto _ = f[0];
  g.resize(n), f.resize(n), f[0] = 0;
  flt_(u32, i, 0, n) b[i] = -g[i];
  core4.bzr(h * 4), core2.bzr(h * 2);
  poly_t a(dfs(dfs, b.data(), n - 1, h, 1));
  return a.resize(n), a.reverse(), a[0] += _, a;
}
}  // namespace tifa_libs::math
CEXP u32 MOD = 998244353;
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
template <class U, class T = U>
requires(sizeof(U) <= sizeof(T))
CEXP vec<T> conv_naive(vec<U> CR l, vec<U> CR r, u32 ans_size = 0) {
  if (l.empty() || r.empty()) return {};
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  const u32 n = (u32)l.size(), m = (u32)r.size();
  vec<T> ans(ans_size);
  if (n < m) flt_(u32, j, 0, m) flt_(u32, i, 0, n) {
      if (i + j >= ans_size) break;
      ans[i + j] += (T)l[i] * (T)r[j];
    }
  else flt_(u32, i, 0, n) flt_(u32, j, 0, m) {
      if (i + j >= ans_size) break;
      ans[i + j] += (T)l[i] * (T)r[j];
    }
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <dft_c DFT_t, std::same_as<TPN DFT_t::data_t> DFT_data_t>
CEXP vec<DFT_data_t>
conv_dft(DFT_t &dft, vec<DFT_data_t> l, vec<DFT_data_t> r, u32 ans_size = 0) {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  if (ans_size < 32) return conv_naive(l, r, ans_size);
  dft.bzr(max({(u32)l.size(),
               (u32)r.size(),
               min(u32(l.size() + r.size() - 1), ans_size)}));
  dft.dif(l), dft.dif(r);
  flt_(u32, i, 0, dft.size()) l[i] *= r[i];
  return dft.dit(l), l.resize(ans_size), l;
}
template <class DFT_t, class mint, class T = u64>
CEXP vec<mint>
conv_dft_u64(DFT_t &dft, vec<T> CR l, vec<T> CR r, u32 ans_size = 0) {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  vec<mint> l_, r_;
  for (l_.reserve(l.size()); auto CR i : l) l_.push_back(i);
  for (r_.reserve(r.size()); auto CR i : r) r_.push_back(i);
  return conv_dft(dft, l_, r_, ans_size);
}
}  // namespace tifa_libs::math
namespace tifa_libs::bit {
template <class T>
CEXP T lowbit(T x) {
  return T(1) << std::countr_zero(x);
}
}  // namespace tifa_libs::bit
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
CEXP u64 qpow_mod(u64 a, u64 b, u64 mod) {
  u64 res(1);
  for (a %= mod; b; b >>= 1, a = mul_mod_u(a, a, mod))
    if (b & 1) res = mul_mod_u(res, a, mod);
  return res;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <std::unsigned_integral T, class It>
CEXP bool is_proot(T g, T m, It pf_begin, It pf_end) {
  if (!g) return false;
  for (; pf_begin != pf_end; ++pf_begin)
    if (qpow_mod(g, (m - 1) / *pf_begin, m) == 1) return false;
  return true;
}
}  // namespace tifa_libs::math
namespace tifa_libs {
template <iterable_c T>
CEXP T uniq(T v) {
  return std::sort(v.begin(), v.end()),
         v.erase(std::unique(v.begin(), v.end()), v.end()), v;
}
template <iterable_c T>
CEXP std::pair<T, vecu> gen_id(T CR v) {
  const T _ = uniq(v);
  vecu _1;
  _1.reserve(v.size());
  flt_(u32, i, 0, (u32)v.size())
    _1.push_back(u32(std::ranges::lower_bound(_, v[i]) - _.begin()));
  return {_, _1};
}
}  // namespace tifa_libs
namespace tifa_libs::rand {
template <class Distri>
class Gen {
  std::conditional_t<sizeof(TPN Distri::result_type) <= 4,
                     std::mt19937,
                     std::mt19937_64>
    re;
  Distri dist;

public:
  using random_engine = decltype(re);
  using result_type = TPN Distri::result_type;
  CEXP Gen(): re(std::random_device{}()), dist() {}
  CEXP Gen(result_type a, result_type b)
    : re(std::random_device{}()), dist(a, b) {}
  CEXP void set_range(result_type a, result_type b) { dist = Distri(a, b); }
  CEXP random_engine &rand_eng() { return re; }
  CEXP Distri &distrib() { return dist; }
  void reset_seed() {
    re.seed((result_type)std::chrono::duration_cast<
              std::conditional_t<sizeof(TPN Distri::result_type) <= 4,
                                 std::chrono::seconds,
                                 std::chrono::nanoseconds>>(
              std::chrono::high_resolution_clock::now().time_since_epoch())
              .count());
  }
  CEXP result_type operator()() { return dist(re); }
  result_type next() { return dist(re); }
};
}  // namespace tifa_libs::rand
namespace tifa_libs::math {
namespace gcd_impl_ {
template <uint_c T, uint_c U>
CEXP std::common_type_t<T, U> gcd__(T u, U v) {
  using W = std::common_type_t<T, U>;
  if (!u || !v) return u ^ v;
  const auto k = std::__countr_zero(u | v);
  u >>= k, v >>= k;
  do {
    if (W _ = v >> std::__countr_zero(v); u > _) v = u - _, u = _;
    else v = _ - u;
  } while (v);
  return u << k;
}
}  // namespace gcd_impl_
template <int_c T, int_c U>
CEXP auto gcd(T a, U b) {
  return gcd_impl_::gcd__((to_uint_t<T>)abs(a), (to_uint_t<U>)abs(b));
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
CEXP bool is_prime(u64 n) {
  if (n <= 2) return n == 2;
  if (~n & 1) return false;
  if (n < 8 || n == 61) return true;
  auto f = [n, d = (n - 1) >> std::countr_zero(n - 1)](auto &&bases) -> bool {
    for (u64 i : bases) {
      if (!(i % n)) continue;
      u64 t = d, y = qpow_mod(i, t, n);
      while (t != n - 1 && y != 1 && y != n - 1) y = mul_mod_u(y, y, n), t *= 2;
      if (y != n - 1 && (~t & 1)) return false;
    }
    return true;
  };
  if (n < (1 << 30)) {
    CEXP u64 bases[3] = {2, 7, 61};
    return f(bases);
  }
  CEXP u64 bases[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  return f(bases);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
namespace pfactors_impl_ {
static rand::Gen<std::uniform_int_distribution<u64>> e;
static auto __ = []() {
  e.reset_seed();
  return 0;
}();
CEXP u64 rho(u64 n) {
  e.set_range(1, n - 1);
  auto f = [n, r = e()](u64 x) { return (mul_mod_u(x, x, n) + r) % n; };
  u64 g = 1, x = 0, y = e(), yy = 0;
  const u32 LIM = 128;
  for (u64 r = 1, q = 1; g == 1; r *= 2) {
    x = y;
    flt_(u64, i, 0, r) y = f(y);
    for (u64 k = 0; g == 1 && k < r; k += LIM) {
      yy = y;
      for (u64 i = 0; i < LIM && i < r - k; ++i)
        q = mul_mod_u(q, (n - (y = f(y)) + x) % n, n);
      g = gcd(q, n);
    }
  }
  if (g == n) do {
      g = gcd((x + (n - (yy = f(yy)))) % n, n);
    } while (g == 1);
  return g == n ? rho(n) : g;
}
CEXP void run(u64 n, vecuu &p) {
  if (n < 2) return;
  if (is_prime(n)) return p.push_back(n);
  const u64 g = rho(n);
  run(n / g, p), run(g, p);
}
}  // namespace pfactors_impl_
template <bool unique = true>
CEXP vecuu pfactors(u64 n) {
  vecuu p;
  if (u32 _ = (u32)std::countr_zero(n) & 63; _) {
    n >>= _;
    if CEXP (unique) p.push_back(2);
    else p.assign(_, 2);
  }
  if (n < 2) return p;
  pfactors_impl_::run(n, p);
  if CEXP (unique) return uniq(p);
  return std::ranges::sort(p), p;
}
CEXP vecp<u64, u32> pf_exp(u64 n) {
  auto p = pfactors<false>(n);
  vecp<u64, u32> ans;
  for (u64 lst = 0; u64 i : p)
    if (i != lst) ans.emplace_back(lst = i, 1);
    else ++ans.back().second;
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
CEXP u64 proot(u64 m) {
  if (m == 2) return 1;
  if (m == 3 || m == 5) return 2;
  if (m == 104857601 || m == 167772161 || m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353 || m == 1004535809) return 3;
  const auto pf = pfactors(m - 1);
  for (u64 g = 2;; ++g)
    if (is_proot(g, m, pf.begin(), pf.end())) return g;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint>
struct NTT {
  using data_t = mint;
  static_assert(is_prime(mint::mod()) && (mint::mod() & 3) == 1,
                "MOD must be prime with 4k+1");
  static CEXP u64 max_size = bit::lowbit(mint::mod() - 1);
  const mint G = proot(mint::mod());
  CEXPE NTT(): root() {}
  CEXP u32 size() const { return (u32)root.size(); }
  CEXP void bzr(u32 len = max_size) {
    const u32 n = std::bit_ceil(len);
    assert(n <= max_size);
    if (n == size()) return;
    root.resize(n), root[0] = 1;
    const mint w = qpow(G, (mint::mod() - 1) / n);
    flt_(u32, i, 1, n) root[i] = root[i - 1] * w;
  }
  CEXP void dif(vec<mint> &f, u32 n = 0) const {
    assert(size());
    if (!n) n = size();
    if (f.size() < n) f.resize(n);
    assert(std::has_single_bit(n) && n <= size());
    for (u32 i = n / 2, d = 1; i; i /= 2, d *= 2)
      for (u32 j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint u, t;
        for (u32 k = 0; k < i; ++k, w += d)
          f[j | k] = (u = f[j | k]) + (t = f[i | j | k]),
                f[i | j | k] = (u - t) * (*w);
      }
  }
  CEXP void dit(vec<mint> &f, u32 n = 0) const {
    assert(size());
    if (!n) n = size();
    if (f.size() < n) f.resize(n);
    assert(std::has_single_bit(n) && n <= size());
    for (u32 i = 1, d = n / 2; d; i *= 2, d /= 2)
      for (u32 j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint t;
        for (u32 k = 0; k < i; ++k, w += d)
          f[i | j | k] = f[j | k] - (t = f[i | j | k] * (*w)), f[j | k] += t;
      }
    std::reverse(f.begin() + 1, f.end());
    const mint t = mint(n).inv();
    flt_(u32, i, 0, n) f[i] *= t;
  }

private:
  vec<mint> root;
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
namespace polyntt_impl_ {
template <class mint>
struct cconv_ntt: public NTT<mint> {
  static CEXP auto ct_cat = ct_NTT;
  CEXP void conv(vec<mint> &l, vec<mint> CR r, u32 sz = 0) {
    l = conv_dft<cconv_ntt, mint>(*this, l, r, sz);
  }
};
}  // namespace polyntt_impl_
template <class mint>
using polyntt = poly<mint, polyntt_impl_::cconv_ntt<mint>>;
}  // namespace tifa_libs::math
using mint = tifa_libs::math::mint_s30<MOD>;
using poly = tifa_libs::math::polyntt<mint>;
int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  poly f(n + 1), g(m + 1);
  tifa_libs::fin >> f.data() >> g.data();
  tifa_libs::fout << tifa_libs::math::comp_fps(f, g).data();
  return 0;
}
