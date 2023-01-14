#include <bits/stdc++.h>
#include <bits/stdtr1c++.h>
#include <ext/algorithm>
#include <ext/rb_tree>
#include <ext/rope>
#include <ext/vstring.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
template <class Tp>
using vc = std::vector<Tp>;
namespace NdVector {
template <size_t N, class Tp>
struct ndvector: public std::vector<ndvector<N - 1, Tp>> {
  static_assert(N > 0, "N should be positive");
  using base_tp = ndvector<N - 1, Tp>;
  using base = std::vector<base_tp>;
  using self = ndvector<N, Tp>;
  template <class T, typename... Ts>
  ndvector(T &&n, Ts &&...args): base(n, base_tp(args...)) {}
  constexpr size_t dim() const { return N; }
  template <class T>
  void fill(T &&x) {
    for (auto &i : *this) i.fill(x);
  }
};
template <class Tp>
struct ndvector<1, Tp>: public std::vector<Tp> {
  using base = std::vector<Tp>;
  using self = ndvector<1, Tp>;
  template <class T>
  ndvector(T &&n): base(n) {}
  constexpr size_t dim() const { return 1; }
  template <class T>
  void fill(T &&x) {
    std::fill(this->begin(), this->end(), x);
  }
};
}  // namespace NdVector
struct CustomHash {
  static constexpr uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static constexpr size_t append(size_t x, size_t y) {
    return x ^ (y >> 1) ^ ((y & 1) << (sizeof(size_t) * 8 - 1));
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
      std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
  template <class Tp, class Up>
  size_t operator()(std::pair<Tp, Up> const &p) const {
    return append((*this)(p.first), (*this)(p.second));
  }
  template <typename... Ts>
  size_t operator()(std::tuple<Ts...> const &tp) const {
    size_t ret = 0;
    std::apply(
      [&](Ts const &...targs) { ((ret = append(ret, (*this)(targs))), ...); },
      tp);
    return ret;
  }
  template <
    class Tp,
    std::enable_if_t<std::is_same<decltype(std::declval<Tp>().begin()),
                                  typename Tp::iterator>::value &&
                     std::is_same<decltype(std::declval<Tp>().end()),
                                  typename Tp::iterator>::value> * = nullptr>
  size_t operator()(Tp const &tp) const {
    size_t ret = 0;
    for (auto &&i : tp) ret = append(ret, (*this)(i));
    return ret;
  }
};
using u32 = uint32_t;
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
}
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
}
template <class Tp>
constexpr auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
#define TPL_SIZE_(Tuple) std::tuple_size_v<std::remove_reference_t<Tuple>>
namespace tuple_detail_ {
template <std::size_t Begin, class Tuple, std::size_t... Is>
constexpr auto subtuple_impl_(Tuple &&t, std::index_sequence<Is...>) {
  return std::make_tuple(std::get<Is + Begin>(t)...);
}
template <class Tuple, class BinOp, std::size_t... Is>
constexpr auto
apply2_impl_(BinOp &&f, Tuple &&lhs, Tuple &&rhs, std::index_sequence<Is...>) {
  return std::make_tuple(
    std::forward<BinOp>(f)(std::get<Is>(lhs), std::get<Is>(rhs))...);
}
}  // namespace tuple_detail_
template <std::size_t Begin, std::size_t Len, class Tuple>
constexpr auto subtuple(Tuple &&t) {
  static_assert(Begin <= TPL_SIZE_(Tuple) && Len <= TPL_SIZE_(Tuple) &&
                  Begin + Len <= TPL_SIZE_(Tuple),
                "Out of range");
  return tuple_detail_::subtuple_impl_<Begin>(t,
                                              std::make_index_sequence<Len>());
}
template <std::size_t Pos, class Tp, class Tuple>
constexpr auto tuple_push(Tp &&v, Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        std::make_tuple(v),
                        subtuple<Pos, TPL_SIZE_(Tuple) - Pos>(t));
}
template <class Tp, class Tuple>
constexpr auto tuple_push_front(Tp &&v, Tuple &&t) {
  return tuple_push<0>(v, t);
}
template <class Tp, class Tuple>
constexpr auto tuple_push_back(Tp &&v, Tuple &&t) {
  return tuple_push<TPL_SIZE_(Tuple)>(v, t);
}
template <std::size_t Pos, class Tuple>
constexpr auto tuple_pop(Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        subtuple<Pos + 1, TPL_SIZE_(Tuple) - Pos - 1>(t));
}
template <class Tuple>
constexpr auto tuple_pop_front(Tuple &&t) {
  return tuple_pop<0>(t);
}
template <class Tuple>
constexpr auto tuple_pop_back(Tuple &&t) {
  return tuple_pop<TPL_SIZE_(Tuple) - 1>(t);
}
template <class Tuple, class BinOp>
constexpr auto apply2(BinOp &&f, Tuple &&lhs, Tuple &&rhs) {
  return tuple_detail_::apply2_impl_(
    f, lhs, rhs, std::make_index_sequence<TPL_SIZE_(Tuple)>());
}
#define OO_PTEQ_(op)                                                          \
  template <class Tp, class Up>                                               \
  constexpr auto operator op(std::pair<Tp, Up> lhs,                           \
                             const std::pair<Tp, Up> &rhs) {                  \
    return std::pair<Tp, Up>{lhs.first op rhs.first,                          \
                             lhs.second op rhs.second};                       \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op(std::tuple<Ts...> const &lhs,                    \
                             std::tuple<Ts...> const &rhs) {                  \
    return apply2([](auto &&l, auto &&r) { return l op r; }, lhs, rhs);       \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator op##=(std::pair<Tp, Up> &lhs,         \
                                              const std::pair<Tp, Up> &rhs) { \
    lhs.first op## = rhs.first;                                               \
    lhs.second op## = rhs.second;                                             \
    return lhs;                                                               \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op##=(std::tuple<Ts...> &lhs,                       \
                                const std::tuple<Ts...> &rhs) {               \
    return lhs = lhs op rhs;                                                  \
  }
OO_PTEQ_(+)
OO_PTEQ_(-)
OO_PTEQ_(*)
OO_PTEQ_(/)
OO_PTEQ_(%)
OO_PTEQ_(&)
OO_PTEQ_(|)
OO_PTEQ_(^)
OO_PTEQ_(<<)
OO_PTEQ_(>>)
#undef OO_PTEQ_
#undef TPL_SIZE_
template <class Tp, class Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <typename... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p);
  return is;
}
template <typename... Ts>
std::ostream &operator<<(std::ostream &os, const std::tuple<Ts...> &p) {
  std::apply(
    [&](Ts const &...targs) {
      std::size_t n{0};
      ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
    },
    p);
  return os;
}
template <
  class Ch,
  class Tr,
  class Ct,
  std::enable_if_t<std::is_same<decltype(std::declval<Ct>().begin()),
                                typename Ct::iterator>::value &&
                   std::is_same<decltype(std::declval<Ct>().end()),
                                typename Ct::iterator>::value> * = nullptr>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Ct &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
const u32 OFFSET = 5;
const u32 N = 5e5 + OFFSET;
using namespace std;
namespace atcoder {
namespace internal {
#if __cplusplus >= 202002L
using std::bit_ceil;
unsigned int bit_ceil(unsigned int n) {
  unsigned int x = 1;
  while (x < (unsigned int)(n)) x *= 2;
  return x;
}
int countr_zero(unsigned int n) { return __builtin_ctz(n); }
constexpr int countr_zero_constexpr(unsigned int n) {
  int x = 0;
  while (!(n & (1 << x))) x++;
  return x;
}
}
}
namespace atcoder {
namespace internal {
constexpr long long safe_mod(long long x, long long m) {
  x %= m;
  if (x < 0) x += m;
  return x;
}
struct barrett {
  unsigned int _m;
  unsigned long long im;
  explicit barrett(unsigned int m)
    : _m(m), im((unsigned long long)(-1) / m + 1) {}
  unsigned int umod() const { return _m; }
  unsigned int mul(unsigned int a, unsigned int b) const {
    unsigned long long z = a;
    z *= b;
    unsigned long long x =
      (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
    unsigned long long y = x * _m;
    return (unsigned int)(z - y + (z < y ? _m : 0));
  }
};
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
  if (m == 1) return 0;
  unsigned int _m = (unsigned int)(m);
  unsigned long long r = 1;
  unsigned long long y = safe_mod(x, m);
  while (n) {
    if (n & 1) r = (r * y) % _m;
    y = (y * y) % _m;
    n >>= 1;
  }
  return r;
}
constexpr bool is_prime_constexpr(int n) {
  if (n <= 1) return false;
  if (n == 2 || n == 7 || n == 61) return true;
  if (n % 2 == 0) return false;
  long long d = n - 1;
  while (d % 2 == 0) d /= 2;
  constexpr long long bases[3] = {2, 7, 61};
  for (long long a : bases) {
    long long t = d;
    long long y = pow_mod_constexpr(a, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = y * y % n;
      t <<= 1;
    }
    if (y != n - 1 && t % 2 == 0) { return false; }
  }
  return true;
}
template <int n>
constexpr bool is_prime = is_prime_constexpr(n);
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
  a = safe_mod(a, b);
  if (a == 0) return {b, 0};
  long long s = b, t = a;
  long long m0 = 0, m1 = 1;
  while (t) {
    long long u = s / t;
    s -= t * u;
    m0 -= m1 * u;
    auto tmp = s;
    s = t;
    t = tmp;
    tmp = m0;
    m0 = m1;
    m1 = tmp;
  }
  if (m0 < 0) m0 += b / s;
  return {s, m0};
}
constexpr int primitive_root_constexpr(int m) {
  if (m == 2) return 1;
  if (m == 167772161) return 3;
  if (m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353) return 3;
  int divs[20] = {};
  divs[0] = 2;
  int cnt = 1;
  int x = (m - 1) / 2;
  while (x % 2 == 0) x /= 2;
  for (int i = 3; (long long)(i)*i <= x; i += 2) {
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) { x /= i; }
    }
  }
  if (x > 1) { divs[cnt++] = x; }
  for (int g = 2;; g++) {
    bool ok = true;
    for (int i = 0; i < cnt; i++) {
      if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
}
template <int m>
constexpr int primitive_root = primitive_root_constexpr(m);
unsigned long long floor_sum_unsigned(unsigned long long n,
                                      unsigned long long m,
                                      unsigned long long a,
                                      unsigned long long b) {
  unsigned long long ans = 0;
  while (true) {
    if (a >= m) {
      ans += n * (n - 1) / 2 * (a / m);
      a %= m;
    }
    if (b >= m) {
      ans += n * (b / m);
      b %= m;
    }
    unsigned long long y_max = a * n + b;
    if (y_max < m) break;
    n = (unsigned long long)(y_max / m);
    b = (unsigned long long)(y_max % m);
    std::swap(m, a);
  }
  return ans;
}
}  // namespace internal
}  // namespace atcoder
namespace atcoder {
namespace internal {
template <class T>
using is_signed_int128 =
  typename std::conditional<std::is_same<T, __int128_t>::value ||
                              std::is_same<T, __int128>::value,
                            std::true_type,
                            std::false_type>::type;
template <class T>
using is_unsigned_int128 =
  typename std::conditional<std::is_same<T, __uint128_t>::value ||
                              std::is_same<T, unsigned __int128>::value,
                            std::true_type,
                            std::false_type>::type;
template <class T>
using make_unsigned_int128 =
  typename std::conditional<std::is_same<T, __int128_t>::value,
                            __uint128_t,
                            unsigned __int128>;
template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value ||
                                                is_signed_int128<T>::value ||
                                                is_unsigned_int128<T>::value,
                                              std::true_type,
                                              std::false_type>::type;
template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                                                 std::is_signed<T>::value) ||
                                                  is_signed_int128<T>::value,
                                                std::true_type,
                                                std::false_type>::type;
template <class T>
using is_unsigned_int =
  typename std::conditional<(is_integral<T>::value &&
                             std::is_unsigned<T>::value) ||
                              is_unsigned_int128<T>::value,
                            std::true_type,
                            std::false_type>::type;
is_signed_int128<T>::value, make_unsigned_int128<T>,
  typename std::conditional<std::is_signed<T>::value,
                            std::make_unsigned<T>,
                            std::common_type<T>>::type > ::type;
template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;
template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;
}  // namespace internal
}  // namespace atcoder
namespace atcoder {
namespace internal {
struct modint_base {};
struct static_modint_base: modint_base {};
}  // namespace internal
template <int m, std::enable_if_t<(1 <= m)> * = nullptr>
struct static_modint: internal::static_modint_base {
  using mint = static_modint;

public:
  static constexpr int mod() { return m; }
  static mint raw(int v) {
    mint x;
    x._v = v;
    return x;
  }
  static_modint(): _v(0) {}
  template <class T, internal::is_signed_int_t<T> * = nullptr>
  static_modint(T v) {
    long long x = (long long)(v % (long long)(umod()));
    if (x < 0) x += umod();
    _v = (unsigned int)(x);
  }
  template <class T, internal::is_unsigned_int_t<T> * = nullptr>
  static_modint(T v) {
    _v = (unsigned int)(v % umod());
  }
  unsigned int val() const { return _v; }
  mint &operator++() {
    _v++;
    if (_v == umod()) _v = 0;
    return *this;
  }
  mint &operator--() {
    if (_v == 0) _v = umod();
    _v--;
    return *this;
  }
  mint operator++(int) {
    mint result = *this;
    ++*this;
    return result;
  }
  mint operator--(int) {
    mint result = *this;
    --*this;
    return result;
  }
  mint &operator+=(const mint &rhs) {
    _v += rhs._v;
    if (_v >= umod()) _v -= umod();
    return *this;
  }
  mint &operator-=(const mint &rhs) {
    _v -= rhs._v;
    if (_v >= umod()) _v += umod();
    return *this;
  }
  mint &operator*=(const mint &rhs) {
    unsigned long long z = _v;
    z *= rhs._v;
    _v = (unsigned int)(z % umod());
    return *this;
  }
  mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }
  mint operator+() const { return *this; }
  mint operator-() const { return mint() - *this; }
  mint pow(long long n) const {
    assert(0 <= n);
    mint x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  mint inv() const {
    if (prime) {
      assert(_v);
      return pow(umod() - 2);
    } else {
      auto eg = internal::inv_gcd(_v, m);
      assert(eg.first == 1);
      return eg.second;
    }
  }
  friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }
  friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }
  friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }
  friend mint operator/(const mint &lhs, const mint &rhs) {
    return mint(lhs) /= rhs;
  }
  friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs._v == rhs._v;
  }
  friend bool operator!=(const mint &lhs, const mint &rhs) {
    return lhs._v != rhs._v;
  }

private:
  unsigned int _v;
  static constexpr unsigned int umod() { return m; }
  static constexpr bool prime = internal::is_prime<m>;
};
template <int id>
struct dynamic_modint: internal::modint_base {
  using mint = dynamic_modint;

public:
  static int mod() { return (int)(bt.umod()); }
  static void set_mod(int m) {
    assert(1 <= m);
    bt = internal::barrett(m);
  }
  static mint raw(int v) {
    mint x;
    x._v = v;
    return x;
  }
  dynamic_modint(): _v(0) {}
  template <class T, internal::is_signed_int_t<T> * = nullptr>
  dynamic_modint(T v) {
    long long x = (long long)(v % (long long)(mod()));
    if (x < 0) x += mod();
    _v = (unsigned int)(x);
  }
  template <class T, internal::is_unsigned_int_t<T> * = nullptr>
  dynamic_modint(T v) {
    _v = (unsigned int)(v % mod());
  }
  unsigned int val() const { return _v; }
  mint &operator++() {
    _v++;
    if (_v == umod()) _v = 0;
    return *this;
  }
  mint &operator--() {
    if (_v == 0) _v = umod();
    _v--;
    return *this;
  }
  mint operator++(int) {
    mint result = *this;
    ++*this;
    return result;
  }
  mint operator--(int) {
    mint result = *this;
    --*this;
    return result;
  }
  mint &operator+=(const mint &rhs) {
    _v += rhs._v;
    if (_v >= umod()) _v -= umod();
    return *this;
  }
  mint &operator-=(const mint &rhs) {
    _v += mod() - rhs._v;
    if (_v >= umod()) _v -= umod();
    return *this;
  }
  mint &operator*=(const mint &rhs) {
    _v = bt.mul(_v, rhs._v);
    return *this;
  }
  mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }
  mint operator+() const { return *this; }
  mint operator-() const { return mint() - *this; }
  mint pow(long long n) const {
    assert(0 <= n);
    mint x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  mint inv() const {
    auto eg = internal::inv_gcd(_v, mod());
    assert(eg.first == 1);
    return eg.second;
  }
  friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }
  friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }
  friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }
  friend mint operator/(const mint &lhs, const mint &rhs) {
    return mint(lhs) /= rhs;
  }
  friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs._v == rhs._v;
  }
  friend bool operator!=(const mint &lhs, const mint &rhs) {
    return lhs._v != rhs._v;
  }

private:
  unsigned int _v;
  static internal::barrett bt;
  static unsigned int umod() { return bt.umod(); }
};
template <int id>
internal::barrett dynamic_modint<id>::bt(998244353);
namespace internal {
template <class T>
using is_static_modint = std::is_base_of<internal::static_modint_base, T>;
template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;
template <class>
struct is_dynamic_modint: public std::false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>>: public std::true_type {};
}  // namespace internal
}  // namespace atcoder
namespace atcoder {
namespace internal {
template <class mint,
          int g = internal::primitive_root<mint::mod()>,
          internal::is_static_modint_t<mint> * = nullptr>
struct fft_info {
  static constexpr int rank2 = countr_zero_constexpr(mint::mod() - 1);
  std::array<mint, rank2 + 1> root;
  std::array<mint, rank2 + 1> iroot;
  std::array<mint, std::max(0, rank2 - 2 + 1)> rate2;
  std::array<mint, std::max(0, rank2 - 2 + 1)> irate2;
  std::array<mint, std::max(0, rank2 - 3 + 1)> rate3;
  std::array<mint, std::max(0, rank2 - 3 + 1)> irate3;
  fft_info() {
    root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);
    iroot[rank2] = root[rank2].inv();
    for (int i = rank2 - 1; i >= 0; i--) {
      root[i] = root[i + 1] * root[i + 1];
      iroot[i] = iroot[i + 1] * iroot[i + 1];
    }
    {
      mint prod = 1, iprod = 1;
      for (int i = 0; i <= rank2 - 2; i++) {
        rate2[i] = root[i + 2] * prod;
        irate2[i] = iroot[i + 2] * iprod;
        prod *= iroot[i + 2];
        iprod *= root[i + 2];
      }
    }
    {
      mint prod = 1, iprod = 1;
      for (int i = 0; i <= rank2 - 3; i++) {
        rate3[i] = root[i + 3] * prod;
        irate3[i] = iroot[i + 3] * iprod;
        prod *= iroot[i + 3];
        iprod *= root[i + 3];
      }
    }
  }
};
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
void butterfly(std::vector<mint> &a) {
  int n = int(a.size());
  int h = internal::countr_zero((unsigned int)n);
  static const fft_info<mint> info;
  int len = 0;
  while (len < h) {
    if (h - len == 1) {
      int p = 1 << (h - len - 1);
      mint rot = 1;
      for (int s = 0; s < (1 << len); s++) {
        int offset = s << (h - len);
        for (int i = 0; i < p; i++) {
          auto l = a[i + offset];
          auto r = a[i + offset + p] * rot;
          a[i + offset] = l + r;
          a[i + offset + p] = l - r;
        }
        if (s + 1 != (1 << len))
          rot *= info.rate2[countr_zero(~(unsigned int)(s))];
      }
      len++;
    } else {
      int p = 1 << (h - len - 2);
      mint rot = 1, imag = info.root[2];
      for (int s = 0; s < (1 << len); s++) {
        mint rot2 = rot * rot;
        mint rot3 = rot2 * rot;
        int offset = s << (h - len);
        for (int i = 0; i < p; i++) {
          auto mod2 = 1ULL * mint::mod() * mint::mod();
          auto a0 = 1ULL * a[i + offset].val();
          auto a1 = 1ULL * a[i + offset + p].val() * rot.val();
          auto a2 = 1ULL * a[i + offset + 2 * p].val() * rot2.val();
          auto a3 = 1ULL * a[i + offset + 3 * p].val() * rot3.val();
          auto a1na3imag = 1ULL * mint(a1 + mod2 - a3).val() * imag.val();
          auto na2 = mod2 - a2;
          a[i + offset] = a0 + a2 + a1 + a3;
          a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
          a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
          a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
        }
        if (s + 1 != (1 << len))
          rot *= info.rate3[countr_zero(~(unsigned int)(s))];
      }
      len += 2;
    }
  }
}
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
void butterfly_inv(std::vector<mint> &a) {
  int n = int(a.size());
  int h = internal::countr_zero((unsigned int)n);
  static const fft_info<mint> info;
  int len = h;
  while (len) {
    if (len == 1) {
      int p = 1 << (h - len);
      mint irot = 1;
      for (int s = 0; s < (1 << (len - 1)); s++) {
        int offset = s << (h - len + 1);
        for (int i = 0; i < p; i++) {
          auto l = a[i + offset];
          auto r = a[i + offset + p];
          a[i + offset] = l + r;
          a[i + offset + p] =
            (unsigned long long)(mint::mod() + l.val() - r.val()) * irot.val();
        }
        if (s + 1 != (1 << (len - 1)))
          irot *= info.irate2[countr_zero(~(unsigned int)(s))];
      }
      len--;
    } else {
      int p = 1 << (h - len);
      mint irot = 1, iimag = info.iroot[2];
      for (int s = 0; s < (1 << (len - 2)); s++) {
        mint irot2 = irot * irot;
        mint irot3 = irot2 * irot;
        int offset = s << (h - len + 2);
        for (int i = 0; i < p; i++) {
          auto a0 = 1ULL * a[i + offset + 0 * p].val();
          auto a1 = 1ULL * a[i + offset + 1 * p].val();
          auto a2 = 1ULL * a[i + offset + 2 * p].val();
          auto a3 = 1ULL * a[i + offset + 3 * p].val();
          auto a2na3iimag =
            1ULL * mint((mint::mod() + a2 - a3) * iimag.val()).val();
          a[i + offset] = a0 + a1 + a2 + a3;
          a[i + offset + 1 * p] =
            (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();
          a[i + offset + 2 * p] =
            (a0 + a1 + (mint::mod() - a2) + (mint::mod() - a3)) * irot2.val();
          a[i + offset + 3 * p] =
            (a0 + (mint::mod() - a1) + (mint::mod() - a2na3iimag)) *
            irot3.val();
        }
        if (s + 1 != (1 << (len - 2)))
          irot *= info.irate3[countr_zero(~(unsigned int)(s))];
      }
      len -= 2;
    }
  }
}
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution_naive(const std::vector<mint> &a,
                                    const std::vector<mint> &b) {
  int n = int(a.size()), m = int(b.size());
  std::vector<mint> ans(n + m - 1);
  if (n < m) {
    for (int j = 0; j < m; j++) {
      for (int i = 0; i < n; i++) { ans[i + j] += a[i] * b[j]; }
    }
  } else {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) { ans[i + j] += a[i] * b[j]; }
    }
  }
  return ans;
}
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution_fft(std::vector<mint> a, std::vector<mint> b) {
  int n = int(a.size()), m = int(b.size());
  int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
  a.resize(z);
  internal::butterfly(a);
  b.resize(z);
  internal::butterfly(b);
  for (int i = 0; i < z; i++) { a[i] *= b[i]; }
  internal::butterfly_inv(a);
  a.resize(n + m - 1);
  mint iz = mint(z).inv();
  for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
  return a;
}
}  // namespace internal
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution(std::vector<mint> &&a, std::vector<mint> &&b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
  assert((mint::mod() - 1) % z == 0);
  if (std::min(n, m) <= 60) return convolution_naive(a, b);
  return internal::convolution_fft(a, b);
}
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution(const std::vector<mint> &a,
                              const std::vector<mint> &b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
  assert((mint::mod() - 1) % z == 0);
  if (std::min(n, m) <= 60) return convolution_naive(a, b);
  return internal::convolution_fft(a, b);
}
template <unsigned int mod = 998244353,
          class T,
          std::enable_if_t<internal::is_integral<T>::value> * = nullptr>
std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  using mint = static_modint<mod>;
  int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
  assert((mint::mod() - 1) % z == 0);
  std::vector<mint> a2(n), b2(m);
  for (int i = 0; i < n; i++) { a2[i] = mint(a[i]); }
  for (int i = 0; i < m; i++) { b2[i] = mint(b[i]); }
  auto c2 = convolution(std::move(a2), std::move(b2));
  std::vector<T> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) { c[i] = c2[i].val(); }
  return c;
}
std::vector<long long> convolution_ll(const std::vector<long long> &a,
                                      const std::vector<long long> &b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  static constexpr unsigned long long MOD1 = 754974721;
  static constexpr unsigned long long MOD2 = 167772161;
  static constexpr unsigned long long MOD3 = 469762049;
  static constexpr unsigned long long M2M3 = MOD2 * MOD3;
  static constexpr unsigned long long M1M3 = MOD1 * MOD3;
  static constexpr unsigned long long M1M2 = MOD1 * MOD2;
  static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;
  static constexpr unsigned long long i1 =
    internal::inv_gcd(MOD2 * MOD3, MOD1).second;
  static constexpr unsigned long long i2 =
    internal::inv_gcd(MOD1 * MOD3, MOD2).second;
  static constexpr unsigned long long i3 =
    internal::inv_gcd(MOD1 * MOD2, MOD3).second;
  static constexpr int MAX_AB_BIT = 24;
  static_assert(MOD1 % (1ull << MAX_AB_BIT) == 1,
                "MOD1 isn't enough to support an array length of 2^24.");
  static_assert(MOD2 % (1ull << MAX_AB_BIT) == 1,
                "MOD2 isn't enough to support an array length of 2^24.");
  static_assert(MOD3 % (1ull << MAX_AB_BIT) == 1,
                "MOD3 isn't enough to support an array length of 2^24.");
  assert(n + m - 1 <= (1 << MAX_AB_BIT));
  auto c1 = convolution<MOD1>(a, b);
  auto c2 = convolution<MOD2>(a, b);
  auto c3 = convolution<MOD3>(a, b);
  std::vector<long long> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) {
    unsigned long long x = 0;
    x += (c1[i] * i1) % MOD1 * M2M3;
    x += (c2[i] * i2) % MOD2 * M1M3;
    x += (c3[i] * i3) % MOD3 * M1M2;
    long long diff =
      c1[i] - internal::safe_mod((long long)(x), (long long)(MOD1));
    if (diff < 0) diff += MOD1;
    static constexpr unsigned long long offset[5] = {
      0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
    x -= offset[diff % 5];
    c[i] = x;
  }
  return c;
}
}  // namespace atcoder
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  vc<long long> a(n + 1), b(m + 1);
  for (auto &i : a) cin >> i;
  for (auto &i : b) cin >> i;
  cout << atcoder::convolution_ll(a, b);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
