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
using u32 = uint32_t;
using u64 = uint64_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
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
const u32 N = 1e6 + OFFSET;
const u32 M = 6 + OFFSET;
using namespace std;
namespace DataGen {
typedef unsigned long long u64;
typedef unsigned int u32;
u32 MT[624], idx;
void _init(u32 seed) {
  MT[0] = seed;
  idx = 0;
  for (int i = 1; i < 624; ++i)
    MT[i] = (0x6c078965 * (MT[i - 1] ^ ((MT[i - 1]) >> 30) + i));
}
void _gene() {
  for (int i = 0; i < 624; ++i) {
    int x = MT[i] & 0x80000000 + (MT[(i + 1) % 624] & 0x7fffffff);
    MT[i] = MT[(i + 397) % 624] ^ (x >> 1);
    if (x & 2) MT[i] ^= 0x9908b0df;
  }
}
u32 _calc() {
  if (!idx) _gene();
  int x = MT[idx];
  x ^= x >> 11, x ^= (x << 7) & (0x9d2c5680);
  x ^= (x << 15) & 0xefc60000, x ^= x >> 18;
  idx = (idx + 1) % 624;
  return x;
}
u64 _get() {
  u64 ret = _calc() * _calc();
  return ret;
}
u64 _get(u64 _l, u64 _r) { return _get() % (_r - _l + 1ull) + _l; }
void input(int &_n, int &_m, int &_q, int *_S, int *_L, u64 *_W, int *_K) {
  u32 seed;
  scanf("%d%d%d%u", &_n, &_m, &_q, &seed);
  _init(seed);
  int i = 1;
  if (_n > 100)
    for (; i <= _q / 4; ++i) {
      int _a = _get(1, _n - 100), _b = _get(_a + _m, _a + _m + 1),
          _l = _b - _a + 1, _k = _get(0, _m);
      u64 _w = _get();
      _S[i] = _a, _L[i] = _l, _W[i] = _w, _K[i] = _k;
    }
  if (_n > 100)
    for (; i <= _q / 2; ++i) {
      int _a = _get(1, 100), _b = _get(_n - 100, _n), _l = _b - _a + 1,
          _k = _get(0, _m);
      u64 _w = _get();
      _S[i] = _a, _L[i] = _l, _W[i] = _w, _K[i] = _k;
    }
  for (; i <= _q; ++i) {
    int _a = _get(1, _n), _b = _get(1, _n);
    if (_a > _b) swap(_a, _b);
    int _l = _b - _a + 1, _k = _get(0, _m);
    u64 _w = _get();
    _S[i] = _a, _L[i] = _l, _W[i] = _w, _K[i] = _k;
  }
}
void output(int n, u64 *R) {
  u64 ret = n ^ _get();
  for (int i = 1; i <= n; i++) ret ^= _get() + R[i];
  printf("%llu\n", ret);
}
}  // namespace DataGen
DataGen::u64 nCr[M][M];
const auto STATIC__ = []() {
  for_(i, 0, M - 1) {
    nCr[i][0] = nCr[i][i] = 1;
    for_(j, 1, i - 1) nCr[i][j] = nCr[i - 1][j - 1] + nCr[i - 1][j];
  }
  return 0;
}();
int s[N], l[N];
DataGen::u64 w[N];
int k[N];
DataGen::u64 r[N][M], ans[N];
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m, q;
  DataGen::input(n, m, q, s, l, w, k);
  for_(i, 1, q) {
    DataGen::u64 _ = w[i], now = 0;
    for_(j, 0, k[i]) {
      now = _ * nCr[k[i]][j];
      r[s[i]][k[i] - j] += now;
      r[s[i] + l[i]][k[i] - j] -= now;
      _ *= 1 - s[i];
    }
  }
  for_(i, 1, n) {
    DataGen::u64 now = 1;
    for_(j, 0, m) {
      ans[i] += now * (r[i][j] += r[i - 1][j]);
      now *= i;
    }
  }
  DataGen::output(n, ans);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = STATIC__;
  solve(i_);
  return 0;
}
