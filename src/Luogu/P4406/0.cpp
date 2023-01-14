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
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
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
const u32 OFFSET = 5;
const u32 N = 5e5 + OFFSET;
const double EPS = 1e-10;
using namespace std;
class SimpsonSolver {
private:
  std::function<double(double)> f;
  static constexpr double
  simpson(double l, double r, double fl, double fmid, double fr) {
    return (fl + 4 * fmid + fr) * (r - l) / 6;
  }
  double asr(double l, double r, double area, double eps) const {
    double mid = r - (r - l) * .5;
    double lmid = mid - (mid - l) * .5, rmid = r - (r - mid) * .5;
    double fl = f(l), flmid = f(lmid), fmid = f(mid), frmid = f(rmid),
           fr = f(r);
    double ls = simpson(l, mid, fl, flmid, fmid),
           rs = simpson(mid, r, fmid, frmid, fr);
    if (std::abs(ls + rs - area) <= 15 * eps)
      return ls + rs + (ls + rs - area) / 15;
    return asr(l, mid, ls, eps * .5) + asr(mid, r, rs, eps * .5);
  }
  double asr(double l, double r, double area, double eps, double dep) const {
    double mid = r - (r - l) * .5;
    double lmid = mid - (mid - l) * .5, rmid = r - (r - mid) * .5;
    double fl = f(l), flmid = f(lmid), fmid = f(mid), frmid = f(rmid),
           fr = f(r);
    double ls = simpson(l, mid, fl, flmid, fmid),
           rs = simpson(mid, r, fmid, frmid, fr);
    if (std::abs(ls + rs - area) <= 15 * eps && dep <= 0)
      return ls + rs + (ls + rs - area) / 15;
    return asr(l, mid, ls, eps * .5, dep - 1) +
           asr(mid, r, rs, eps * .5, dep - 1);
  }

public:
  template <typename Func>
  SimpsonSolver(Func &&func): f(func) {}
  double operator()(double l, double r, double eps) const {
    return asr(l, r, simpson(l, r, f(l), f(r - (r - l) * .5), f(r)), eps);
  }
  double operator()(double l, double r, double eps, double min_dep) const {
    return asr(
      l, r, simpson(l, r, f(l), f(r - (r - l) * .5), f(r)), eps, min_dep);
  }
};
struct Node {
  using Tp = pair<double, double>;
  Tp p1, p2, p3;
  double l, r;
  Node(const Tp &p1_ = {0, 0}, const Tp &p2_ = {0, 0}, const Tp &p3_ = {0, 0})
    : p1(p1_), p2(p2_), p3(p3_) {
    if (p1.first > p2.first) swap(p1, p2);
    if (p1.first > p3.first) swap(p1, p3);
    if (p2.first > p3.first) swap(p2, p3);
    l = p1.first;
    r = p3.first;
  }
  bool inpos(double x) const { return l < x && x < r; }
  pair<double, double> range(double x) const {
    vc<double> ans;
    ans.reserve(2);
    if (p1.first <= x && x < p2.first)
      ans.push_back(p1.second + (p2.second - p1.second) * (x - p1.first) /
                                  (p2.first - p1.first));
    if (p1.first <= x && x < p3.first)
      ans.push_back(p1.second + (p3.second - p1.second) * (x - p1.first) /
                                  (p3.first - p1.first));
    if (p2.first <= x && x < p3.first)
      ans.push_back(p2.second + (p3.second - p2.second) * (x - p2.first) /
                                  (p3.first - p2.first));
    if (ans[0] > ans[1]) return {ans[1], ans[0]};
    return {ans[0], ans[1]};
  }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vc<Node> v;
  v.reserve(n);
  for_(i, 1, n) {
    pair<double, double> p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    v.emplace_back(p1, p2, p3);
  }
  vc<pair<double, double>> seg;
  seg.reserve(n);
  SimpsonSolver rs([&v, &seg](double pos) -> double {
    seg.clear();
    for (auto &&i : v)
      if (i.inpos(pos)) seg.emplace_back(i.range(pos));
    if (seg.empty()) return 0;
    sort(all_(seg));
    double ans = 0, lst = seg.front().first;
    for (auto &&[l, r] : seg)
      if (r - lst > 0) {
        ans += r - max(l, lst);
        lst = r;
      }
    return ans;
  });
  vc<double> pos;
  pos.reserve(n * 2);
  for (auto &&[_, __, ___, l, r] : v) {
    pos.push_back(l);
    pos.push_back(r);
  }
  sort(all_(pos));
  pos.erase(unique(all_(pos)), pos.end());
  double ans = 0;
  for_(i, 1, pos.size() - 1) ans += rs(pos[i - 1], pos[i], EPS, 5);
  cout << fixed << setprecision(2) << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
