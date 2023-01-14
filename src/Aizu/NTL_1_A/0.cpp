namespace tifa_libs::bit {
template <class T>
constexpr int cntr0(T x) {
  constexpr int nd = sizeof(T) * 8;
  static_assert(nd <= 128);
  if (x == 0) return nd;
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  if constexpr (nd <= sizeof(unsigned) * 8) return __builtin_ctz(x);
  else if constexpr (nd <= sizeof(unsigned long) * 8) return __builtin_ctzl(x);
  else if constexpr (nd <= nd_ull) return __builtin_ctzll(x);
  else {
    unsigned long long lo = x & (unsigned long long)(-1);
    if (lo != 0) return __builtin_ctzll(lo);
    unsigned long long hi = x >> nd_ull;
    return __builtin_ctzll(hi) + nd_ull;
  }
}
}  // namespace tifa_libs::bit
#include <bits/stdc++.h>
using i128 = __int128_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;
#undef assert
#define assert(x) 42
namespace tifa_libs::rand {
template <class Distri>
class Gen {
  std::conditional_t<sizeof(typename Distri::result_type) <= 4,
                     std::mt19937,
                     std::mt19937_64>
    re;
  Distri dist;

public:
  using random_engine = decltype(re);
  using result_type = typename Distri::result_type;
  Gen(): re(std::random_device{}()), dist() {}
  Gen(result_type a, result_type b): re(std::random_device{}()), dist(a, b) {}
  void set_range(result_type a, result_type b) { dist = Distri(a, b); }
  random_engine &rand_eng() { return re; }
  Distri &distrib() { return dist; }
  result_type operator()() { return dist(re); }
};
}  // namespace tifa_libs::rand
namespace tifa_libs::bit {
template <class T>
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
template <class T>
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
constexpr u64 qpow_mod(u64 a, u64 b, u64 mod) {
  u64 res(1);
  for (a %= mod; b; b >>= 1, a = mul_mod_u(a, a, mod))
    if (b & 1) res = mul_mod_u(res, a, mod);
  return res;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr bool is_prime(u64 n) {
  if (n <= 2) return n == 2;
  if (~n & 1) return false;
  if (n < 8 || n == 61) return true;
  auto f = [n, d = (n - 1) >> bit::cntr0(n - 1)](auto const &bases) -> bool {
    for (u64 i : bases) {
      if (!(i % n)) continue;
      u64 t = d, y = qpow_mod(i, t, n);
      while (t != n - 1 && y != 1 && y != n - 1) {
        y = mul_mod_u(y, y, n);
        t *= 2;
      }
      if (y != n - 1 && (~t & 1)) return false;
    }
    return true;
  };
  if (n < (1 << 30)) {
    constexpr u64 bases[3] = {2, 7, 61};
    return f(bases);
  }
  constexpr u64 bases[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  return f(bases);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
namespace pfactors_impl_ {
class PollardRho {
  rand::Gen<std::uniform_int_distribution<u64>> e;
  u64 rho(u64 n) {
    e.set_range(2, n - 1);
    auto f = [n, r = e()](u64 x) { return (mul_mod_u(x, x, n) + r) % n; };
    u64 g = 1, x = 0, y = e(), yy = 0;
    const u32 LIM = 128;
    for (u64 r = 1, q = 1; g == 1; r *= 2) {
      x = y;
      for (u64 i = 0; i < r; ++i) y = f(y);
      for (u64 k = 0; g == 1 && k < r; k += LIM) {
        yy = y;
        for (u64 i = 0; i < LIM && i < r - k; ++i)
          q = mul_mod_u(q, (x + (n - (y = f(y)))) % n, n);
        g = std::gcd(q, n);
      }
    }
    if (g == n) do {
        g = std::gcd((x + (n - (yy = f(yy)))) % n, n);
      } while (g == 1);
    return g == n ? rho(n) : g;
  }

public:
  explicit PollardRho(): e() {}
  void operator()(u64 n, std::map<u64, u32> &ans) {
    if (n < 2) return;
    if (is_prime(n)) {
      ++ans[n];
      return;
    }
    auto g = rho(n);
    (*this)(n / g, ans);
    (*this)(g, ans);
  }
};
}  // namespace pfactors_impl_
std::map<u64, u32> pfactors(u64 n) {
  std::map<u64, u32> ans;
  if (n < 2) return ans;
  if (~n & 1) n >>= (ans[2] = (u32)bit::cntr0(n));
  using pfactors_impl_::PollardRho;
  PollardRho()(n, ans);
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs {
constexpr u32 u32tostr_si16(u64 x, char *s) {
  if (x <= 9) {
    *s = (char)(x | 0x30);
    return 1;
  } else if (x <= 99) {
    u64 low = x;
    u64 ll = ((low * 103) >> 9) & 0x1E;
    low += ll * 3;
    ll = ((low & 0xF0) >> 4) | ((low & 0x0F) << 8);
    *(u16 *)s = (u16)(ll | 0x3030);
    return 2;
  }
  return 0;
}
constexpr u32 u32tostr_si32(u64 x, char *s) {
  u64 low = 0, ll = 0;
  u32 digits = 0;
  if (x <= 99) return u32tostr_si16(x, s);
  low = x;
  digits = (low > 999) ? 4 : 3;
  ll = ((low * 5243) >> 19) & 0xFF;
  low -= ll * 100;
  low = (low << 16) | ll;
  ll = ((low * 103) >> 9) & 0x1E001E;
  low += ll * 3;
  ll = ((low & 0x00F000F0) << 28) | (low & 0x000F000F) << 40;
  ll |= 0x3030303000000000;
  u8 *p = (u8 *)&ll;
  if (digits == 4) *(u32 *)s = *(u32 *)(&p[4]);
  else {
    *(u16 *)s = *(u16 *)(&p[5]);
    *(((u8 *)s) + 2) = p[7];
  }
  return digits;
}
constexpr u32 u32tostr(u64 x, char *s) {
  u64 low = 0, ll = 0;
  u32 digits = 0;
  if (x <= 9999) return u32tostr_si32(x, s);
  if (x < 100000000) {
    if ((low = x) > 999999) digits = (low > 9999999) ? 8 : 7;
    else digits = (low > 99999) ? 6 : 5;
  } else {
    u64 high = (x * 0x55E63B89) >> 57;
    low = x - (high * 100000000);
    digits = u32tostr_si16(high, s);
    digits += 8;
  }
  ll = (low * 109951163) >> 40;
  (low -= ll * 10000) |= ll << 32;
  ll = ((low * 5243) >> 19) & 0x000000FF000000FF;
  low -= ll * 100;
  low = (low << 16) | ll;
  ll = ((low * 103) >> 9) & 0x001E001E001E001E;
  low += ll * 3;
  ll = ((low & 0x00F000F000F000F0) >> 4) | (low & 0x000F000F000F000F) << 8;
  ll = (ll >> 32) | (ll << 32) | 0x3030303030303030;
  if (digits >= 8) memcpy(s + digits - 8, &ll, 8);
  else {
    u32 d = digits;
    char *s1 = s, *pll = &(((char *)&ll)[8 - digits]);
    if (d >= 4) {
      memcpy(s1, pll, 4);
      s1 += 4, pll += 4, d -= 4;
    }
    if (d >= 2) {
      memcpy(s1, pll, 2);
      s1 += 2, pll += 2, d -= 2;
    }
    if (d > 0) *(u8 *)s1 = *(u8 *)pll;
  }
  return digits;
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
using remove_cvref_t =
  typename std::remove_cv_t<typename std::remove_reference_t<T>>;
template <class T>
using is_iterable = typename std::conditional_t<
  std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().begin()),
                 typename remove_cvref_t<T>::iterator> &&
    std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().end()),
                   typename remove_cvref_t<T>::iterator>,
  std::true_type,
  std::false_type>;
template <class T>
using is_container = typename std::conditional_t<
  is_iterable<T>::value &&
    !std::is_base_of_v<T, std::basic_string<typename T::value_type>>,
  std::true_type,
  std::false_type>;
template <class T>
using is_char = typename std::conditional_t<std::is_same_v<T, char> ||
                                              std::is_same_v<T, signed char> ||
                                              std::is_same_v<T, unsigned char>,
                                            std::true_type,
                                            std::false_type>;
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
using to_u128 = typename std::
  conditional<std::is_same_v<T, __int128_t>, __uint128_t, unsigned __int128>;
template <class T>
using is_int =
  typename std::conditional_t<std::is_integral_v<T> || is_s128<T>::value ||
                                is_u128<T>::value,
                              std::true_type,
                              std::false_type>;
template <class T>
using is_sint =
  typename std::conditional_t<is_s128<T>::value ||
                                (is_int<T>::value && std::is_signed_v<T>),
                              std::true_type,
                              std::false_type>;
template <class T>
using is_uint =
  typename std::conditional_t<is_u128<T>::value ||
                                (is_int<T>::value && std::is_unsigned_v<T>),
                              std::true_type,
                              std::false_type>;
template <class T>
using to_uint =
  typename std::conditional_t<std::is_same_v<T, i128>,
                              to_u128<T>,
                              typename std::conditional_t<std::is_signed_v<T>,
                                                          std::make_unsigned<T>,
                                                          std::common_type<T>>>;
template <class T>
using is_mint = typename std::conditional_t<
  is_uint<decltype(std::declval<remove_cvref_t<T>>().mod())>::value &&
    is_uint<decltype(std::declval<remove_cvref_t<T>>().val())>::value &&
    is_sint<decltype(std::declval<remove_cvref_t<T>>().sval())>::value,
  std::true_type,
  std::false_type>;
}  // namespace tifa_libs
namespace tifa_libs {
#define fread_unlocked fread
#define fwrite_unlocked fwrite
namespace fastio_impl_ {
template <usz BUF>
class fastin {
  char bf_[BUF], *now_ = bf_, *end_ = bf_;
  FILE *f_;

public:
  explicit fastin(FILE *f = stdin): f_(f) {}
  char get() {
    return now_ == end_ &&
               (end_ = (now_ = bf_) + fread_unlocked(bf_, 1, BUF, f_),
                now_ == end_) ?
             EOF :
             *(now_)++;
  }
  char peek() {
    return now_ == end_ &&
               (end_ = (now_ = bf_) + fread_unlocked(bf_, 1, BUF, f_),
                now_ == end_) ?
             EOF :
             *(now_);
  }
  void rebind(FILE *f) {
    f_ = f;
    now_ = end_ = bf_;
  }
  bool iseof() { return peek() == EOF; }
  template <
    class T,
    std::enable_if_t<is_sint<T>::value && !is_char<T>::value> * = nullptr>
  fastin &read(T &n) {
    bool is_neg = false;
    char ch = get();
    while (!isdigit(ch)) {
      is_neg |= ch == '-';
      ch = get();
    }
    n = 0;
    while (isdigit(ch)) {
      (n *= 10) += ch & 15;
      ch = get();
    }
    if (is_neg) n = -n;
    return *this;
  }
  template <
    class T,
    std::enable_if_t<is_uint<T>::value && !is_char<T>::value> * = nullptr>
  fastin &read(T &n) {
    char ch = get();
    while (!isdigit(ch)) ch = get();
    n = 0;
    while (isdigit(ch)) {
      (n *= 10) += ch & 15;
      ch = get();
    }
    return *this;
  }
  template <class T, std::enable_if_t<is_mint<T>::value> * = nullptr>
  fastin &read(T &n) {
    decltype(std::declval<T>().sval()) x;
    read(x);
    n = T(x);
    return *this;
  }
  template <class T, std::enable_if_t<is_char<T>::value> * = nullptr>
  fastin &read(T &n) {
    while (!isgraph(n = get()));
    return *this;
  }
  fastin &read(char *n) {
    char *n_ = n;
    while (!isgraph(*n_ = get()));
    while (isgraph(*(++n_) = get()));
    *n_ = '\0';
    return *this;
  }
  fastin &read(std::string &n) {
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
  template <typename... Ts>
  fastin &read(std::tuple<Ts...> &p) {
    std::apply([&](Ts &...targs) { ((read(targs)), ...); }, p);
    return *this;
  }
  template <class T, std::enable_if_t<is_container<T>::value> * = nullptr>
  fastin &read(T &p) {
    if (p.begin() == p.end()) return *this;
    for (auto &i : p) read(i);
    return *this;
  }
  fastin &getline(char *n) {
    char *n_ = n;
    while (!isprint(*n_ = get()));
    while (isprint(*(++n_) = get()));
    *n_ = '\0';
    return *this;
  }
  fastin &getline(std::string &n) {
    char n_;
    while (!isprint(n_ = get()));
    n.push_back(n_);
    while (isprint(n_ = get())) n.push_back(n_);
    return *this;
  }
  template <class T, std::enable_if_t<is_char<T>::value> * = nullptr>
  fastin &strict_read(T &n) {
    n = get();
    return *this;
  }
  template <class T>
  fastin &operator>>(T &val) {
    return read(val);
  }
};
template <usz BUF, usz INTBUF>
class fastout {
  char int_bf_[INTBUF], *now_ib_ = int_bf_;
  FILE *f_;
  char *now_, bf_[BUF];
  const char * const end_ = bf_ + BUF;

public:
  explicit fastout(FILE *file = stdout): f_(file), now_(bf_) {}
  fastout &operator=(fastout const &rhs) {
    f_ = rhs.f_;
    now_ = bf_ + (rhs.now_ - rhs.bf_);
    memcpy(bf_, rhs.bf_, sizeof(*bf_) * (rhs.now_ - rhs.bf_));
    return *this;
  }
  fastout(fastout const &rhs) { *this = rhs; }
  ~fastout() { flush(); }
  void flush() {
    fwrite_unlocked(bf_, 1, usz(now_ - bf_), f_);
    now_ = bf_;
  }
  void rebind(FILE *file) { f_ = file; }
  template <class T, std::enable_if_t<is_char<T>::value> * = nullptr>
  fastout &write(T const &n) {
    if (now_ == end_) flush();
    *(now_++) = n;
    return *this;
  }
  fastout &write(const char *n) {
    usz len = strlen(n), l_;
    const char *n_ = n;
    while (now_ + len >= end_) {
      memcpy(now_, n_, l_ = usz(end_ - now_));
      now_ += l_;
      n_ += l_;
      len -= l_;
      flush();
    }
    memcpy(now_, n_, len);
    now_ += len;
    return *this;
  }
  template <
    class T,
    std::enable_if_t<is_sint<T>::value && !is_char<T>::value> * = nullptr>
  fastout &write(T n) {
    if (n < 0) {
      write('-');
      n = -n;
    }
    return write(typename to_uint<T>::type(n));
  }
  template <
    class T,
    std::enable_if_t<is_uint<T>::value && !is_char<T>::value> * = nullptr>
  fastout &write(T n) {
    if constexpr (sizeof(T) <= 4) {
      memset(now_ib_ = int_bf_, 0, 11);
      u32tostr(n, now_ib_);
      return write(now_ib_);
    }
    now_ib_ = int_bf_ + INTBUF - 1;
    do { *(--(now_ib_)) = char(n % 10) | '0'; } while (n /= 10);
    return write(now_ib_);
  }
  template <class T, std::enable_if_t<is_mint<T>::value> * = nullptr>
  fastout &write(T n) {
    return write(n.val());
  }
  fastout &write(std::string const &str) { return write(str.c_str()); }
  template <class T, class U>
  fastout &write(std::pair<T, U> const &p) {
    return write(p.first).space().write(p.second);
  }
  template <typename... Ts>
  fastout &write(std::tuple<Ts...> const &p) {
    std::apply(
      [&](Ts const &...targs) {
        usz n{0};
        ((write(targs).space_if(++n != sizeof...(Ts))), ...);
      },
      p);
    return *this;
  }
  template <class T, std::enable_if_t<is_container<T>::value> * = nullptr>
  fastout &write(T const &p) {
    if (p.begin() == p.end()) return *this;
    auto it = p.begin();
    write(*it++);
    for (; it != p.end(); ++it) space().write(*it);
    return *this;
  }
  fastout &linebreak() { return write('\n'); }
  fastout &linebreak_if(bool flag) { return flag ? linebreak() : *this; }
  fastout &space() { return write(' '); }
  fastout &space_if(bool flag) { return flag ? space() : *this; }
  template <class T>
  fastout &operator<<(T const &val) {
    return write(val);
  }
};
}  // namespace fastio_impl_
fastio_impl_::fastin<0x200005> fin;
fastio_impl_::fastout<0x200005, 41> fout;
}  // namespace tifa_libs
int main() {
  u64 n;
  tifa_libs::fin >> n;
  auto ans = tifa_libs::math::pfactors(n);
  tifa_libs::fout << n << ":";
  for (auto [k, v] : ans)
    for (u32 i = 0; i < v; ++i) tifa_libs::fout << ' ' << k;
  tifa_libs::fout << '\n';
  return 0;
}
