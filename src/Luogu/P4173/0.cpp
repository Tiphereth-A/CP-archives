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
#define all_(a) (a).begin(), (a).end()
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
const double EPS = 1e-6;
const double PI = acos(-1.0);
using namespace std;
namespace FFT {
using CP = std::complex<double>;
const double PI = acos(-1.0);
size_t n = 0;
std::vector<size_t> rev;
void init(size_t m) {
  if (n > m) return;
  n = 1;
  size_t k = 0;
  while (n <= m) {
    n <<= 1;
    ++k;
  }
  rev.resize(n);
  for (size_t i = 0; i < n; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
}
void dft(std::vector<CP> &a, int op) {
  for (size_t i = 0; i < n; ++i)
    if (rev[i] > i) std::swap(a[rev[i]], a[i]);
  for (size_t i = 1; i < n; i <<= 1) {
    CP now(std::cos(PI / i), op * std::sin(PI / i));
    for (size_t j = 0, p = (i << 1); j < n; j += p) {
      CP w(1, 0);
      for (size_t k = 0; k < i; ++k, w = w * now) {
        CP x = a[j + k], y = a[j + k + i] * w;
        a[j + k] = x + y;
        a[j + k + i] = x - y;
      }
    }
  }
  if (op == -1)
    for (size_t i = 0; i < n; ++i) a[i] = {a[i].real() / n, a[i].imag() / n};
}
std::vector<double> conv(std::vector<double> const &a,
                         std::vector<double> const &b) {
  init(a.size() + b.size() - 1);
  std::vector<CP> a_(n), b_(n), c_(n);
  for (size_t i = 0; i < a.size(); ++i) a_[i] = a[i];
  for (size_t i = 0; i < b.size(); ++i) b_[i] = b[i];
  dft(a_, 1);
  dft(b_, 1);
  for (size_t i = 0; i < n; ++i) c_[i] = a_[i] * b_[i];
  dft(c_, -1);
  std::vector<double> c(a.size() + b.size() - 1);
  for (size_t i = 0; i < a.size() + b.size() - 1; ++i) c[i] = c_[i].real();
  return c;
}
}  // namespace FFT
using FFT::conv;
namespace FFT_KMP {
const double EPS = 1e2;
std::vector<size_t> match_normal(std::string_view s, std::string_view t) {
  size_t m = s.size(), n = t.size();
  std::vector<double> a(m), b(n), f(n);
  std::copy(s.begin(), s.end(), a.rbegin());
  std::copy(t.begin(), t.end(), b.begin());
  double T = std::accumulate(
    a.begin(), a.end(), .0, [](auto &&x, auto &&y) { return x + y * y; });
  std::partial_sum(b.begin(), b.end(), f.begin(), [](auto &&x, auto &&y) {
    return x + y * y;
  });
  std::vector<double> g = FFT::conv(a, b);
  std::vector<size_t> res;
  for (size_t i = m - 1; i < n; ++i)
    if (abs(T + f[i] - (i < m ? 0 : f[i - m]) - 2 * g[i]) < EPS)
      res.push_back(i - m + 1);
  return res;
}
std::vector<size_t> match_star(std::string_view s, std::string_view t) {
  size_t m = s.size(), n = t.size();
  std::vector<double> a(m), aa(m), b(n), bb(m);
  for (size_t i = 0; i < m; ++i) a[m - i - 1] = s[i] == '*' ? 0 : s[i];
  aa = a;
  for (size_t i = 0; i < n; ++i) b[i] = t[i] == '*' ? 0 : t[i];
  bb = b;
  std::for_each(aa.begin(), aa.end(), [](auto &&x) { x = x * x * x; });
  std::for_each(bb.begin(), bb.end(), [](auto &&x) { x = x * x * x; });
  std::vector<double> f = FFT::conv(aa, b), g = FFT::conv(a, bb);
  std::for_each(a.begin(), a.end(), [](auto &&x) { x = x * x; });
  std::for_each(b.begin(), b.end(), [](auto &&x) { x = x * x; });
  std::vector<double> h = FFT::conv(a, b);
  std::vector<size_t> res;
  for (size_t i = m - 1; i < n; ++i)
    if (abs(f[i] + g[i] - 2 * h[i]) < EPS) res.push_back(i - m + 1);
  return res;
}
}  // namespace FFT_KMP
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  string a, b;
  cin >> a >> b;
  auto res = FFT_KMP::match_star(a, b);
  for_each(all_(res), [](auto &&x) { ++x; });
  cout << res.size() << '\n' << res;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
