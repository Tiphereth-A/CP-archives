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
using i64 = int64_t;
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
const i64 MOD = 1e9 + 7;
using namespace std;
namespace exEuclid {
template <class T>
struct Node_base {
  T u, r;
  Node_base(T const &u = 0, T const &r = 0): u(u), r(r) {}
};
template <class Node>
constexpr Node qpow(Node a, int64_t b) {
  Node res;
  for (; b; b >>= 1, a = a + a)
    if (b & 1) res = res + a;
  return res;
}
template <class Node>
Node solve(int64_t p, int64_t q, int64_t r, int64_t l, Node a, Node b) {
  auto div = [](int64_t a, int64_t b, int64_t c, int64_t d) -> int64_t {
    return (1.l * a * b + c) / d;
  };
  if (!l) return Node();
  if (p >= q) return solve(p % q, q, r, l, a, qpow(a, p / q) + b);
  int64_t m = div(l, p, r, q);
  if (!m) return qpow(b, l);
  int64_t cnt = l - div(q, m, -r - 1, p);
  return qpow(b, (q - r - 1) / p) + a +
         solve(q, p, (q - r - 1) % p, m - 1, b, a) + qpow(b, cnt);
}
}  // namespace exEuclid
namespace MODINT {
constexpr int64_t safe_mod(int64_t x, int64_t m) {
  return (x %= m) < 0 ? x + m : x;
}
constexpr std::pair<int64_t, int64_t> invgcd(int64_t a, int64_t b) {
  if ((a = safe_mod(a, b)) == 0) return {b, 0};
  int64_t s = b, m0 = 0;
  for (int64_t q = 0, _ = 0, m1 = 1; a;) {
    _ = s - a * (q = s / a);
    s = a;
    a = _;
    _ = m0 - m1 * q;
    m0 = m1;
    m1 = _;
  }
  return {s, m0 + (m0 < 0 ? b / s : 0)};
}
template <uint32_t MOD>
class Mint {
  static_assert(MOD >= 1);
  using self = Mint<MOD>;

protected:
  uint32_t v_;

public:
  static constexpr uint32_t mod() { return MOD; }
  static constexpr self raw(uint32_t v) {
    self x;
    x.v_ = v;
    return x;
  }
  constexpr Mint(): v_(0) {}
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_signed<T>::value> * = nullptr>
  constexpr Mint(T v): Mint() {
    int64_t x = (int64_t)(v % (int64_t)mod());
    v_ = (uint32_t)(x + (x < 0 ? mod() : 0));
  }
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_unsigned<T>::value> * = nullptr>
  constexpr Mint(T v): v_((uint32_t)(v % mod())) {}
  friend std::istream &operator>>(std::istream &is, self &x) {
    int64_t xx;
    is >> xx;
    xx %= mod();
    x.v_ = (uint32_t)(xx + (xx < 0 ? mod() : 0));
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &x) {
    return os << x.v_;
  }
  constexpr const uint32_t &val() const { return v_; }
  constexpr explicit operator uint32_t() const { return val(); }
  constexpr uint32_t &data() { return v_; }
  constexpr self &operator++() {
    if (++v_ == mod()) v_ = 0;
    return *this;
  }
  constexpr self &operator--() {
    if (!v_) v_ = mod();
    --v_;
    return *this;
  }
  constexpr self operator++(int) {
    self result = *this;
    ++*this;
    return result;
  }
  constexpr self operator--(int) {
    self result = *this;
    --*this;
    return result;
  }
  constexpr self &operator+=(const self &rhs) {
    v_ += rhs.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr self &operator-=(const self &rhs) {
    v_ -= rhs.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr self &operator*=(const self &rhs) {
    v_ = (uint32_t)((uint64_t)v_ * rhs.v_ % mod());
    return *this;
  }
  constexpr self &operator/=(const self &rhs) {
    return *this = *this * inverse(rhs);
  }
  constexpr self operator+() const { return *this; }
  constexpr self operator-() const { return self() - *this; }
  constexpr friend self pow(self x, uint64_t y) {
    self res(1);
    for (; y; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }
  constexpr friend self inverse(const self &x) {
    auto &&_ = invgcd(x.v_, self::mod());
    if (_.first != 1) throw std::runtime_error("Inverse not exist");
    return _.second;
  }
  constexpr friend self operator+(self lhs, const self &rhs) {
    return lhs += rhs;
  }
  constexpr friend self operator-(self lhs, const self &rhs) {
    return lhs -= rhs;
  }
  constexpr friend self operator*(self lhs, const self &rhs) {
    return lhs *= rhs;
  }
  constexpr friend self operator/(self lhs, const self &rhs) {
    return lhs /= rhs;
  }
  constexpr friend bool operator==(const self &lhs, const self &rhs) {
    return lhs.v_ == rhs.v_;
  }
  constexpr friend bool operator!=(const self &lhs, const self &rhs) {
    return lhs.v_ != rhs.v_;
  }
};
}  // namespace MODINT
using mint = MODINT::Mint<998244353>;
struct Node final: public exEuclid::Node_base<mint> {
  using base = exEuclid::Node_base<mint>;
  mint i, f, sqr_f, i_f;
  Node(mint const &u = 0,
       mint const &r = 0,
       mint const &i = 0,
       mint const &f = 0,
       mint const &sqr_f = 0,
       mint const &i_f = 0)
    : base(u, r), i(i), f(f), sqr_f(sqr_f), i_f(i_f) {}
  Node operator+(Node const &rhs) const {
    return Node{u + rhs.u,
                r + rhs.r,
                i + rhs.i + r * rhs.r,
                f + rhs.f + u * rhs.r,
                sqr_f + rhs.sqr_f + u * u * rhs.r + 2 * u * rhs.f,
                i_f + rhs.i_f + u * r * rhs.r + u * rhs.i + r * rhs.f};
  }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 n, a, b, c;
  cin >> n >> a >> b >> c;
  Node u{1, 0, 0, 0, 0, 0}, r{0, 1, 1, 0, 0, 0};
  Node ans = exEuclid::qpow(u, b / c) + exEuclid::solve(a, c, b % c, n, u, r);
  cout << (ans.f + b / c) << ' ' << (ans.sqr_f + (b / c) * (b / c)) << ' '
       << ans.i_f << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
