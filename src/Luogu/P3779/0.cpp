#include <bits/stdc++.h>
using u32 = uint32_t;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define intlt2str_(s) STR_____(s)
#define STR_____(s) #s
#define REif_(expression)   \
  if (expression)           \
  throw std::runtime_error( \
    "Line " intlt2str_(__LINE__) ": やだもやだ、無理も無理〜")
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
template <class Tp, class Pred>
Tp binary_search(Pred check, Tp ok, Tp ng) {
  REif_(!check(ok));
  while (std::abs(ok - ng) > 1) {
    Tp x = (ng + ok) / 2;
    (check(x) ? ok : ng) = x;
  }
  return ok;
}
template <class Tp,
          class Pred,
          std::enable_if_t<std::is_floating_point_v<Tp>> * = nullptr>
Tp binary_search_real(Pred check, Tp ok, Tp ng, Tp eps) {
  REif_(!check(ok));
  while (std::abs(ok - ng) > eps) {
    Tp x = (ng + ok) / 2;
    (check(x) ? ok : ng) = x;
  }
  return (ng + ok) / 2;
}
template <class Tp>
auto discretization(Tp &var) -> Tp {
  Tp d__(var);
  std::sort(d__.begin(), d__.end());
  d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
  for (auto &i : var)
    i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
  return d__;
};
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
    return {lhs.first op rhs.first, lhs.second op rhs.second};                \
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
template <class Ch,
          class Tr,
          class Ct,
          std::enable_if_t<std::is_same_v<decltype(std::declval<Ct>().begin()),
                                          typename Ct::iterator> &&
                           std::is_same_v<decltype(std::declval<Ct>().end()),
                                          typename Ct::iterator>> * = nullptr>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Ct &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
const u32 OFFSET = 5;
const u32 N = 3e5 + OFFSET;
const double PI = acos(-1.0);
using namespace std;
class SimpsonSolver {
protected:
  const double eps__;
  const int least_dep__;
  template <typename Func>
  constexpr double simpson(double l, double r, Func &&func) const {
    return (func(l) + 4 * func(r - (r - l) * .5) + func(r)) * (r - l) / 6;
  }
  template <typename Func>
  double
  asr(double l, double r, double area, double eps, int dep, Func &&func) const {
    double mid = r - (r - l) * .5;
    double ls = simpson(l, mid, func), rs = simpson(mid, r, func);
    if (std::abs(ls + rs - area) <= 15 * eps && dep < 0)
      return ls + rs + (ls + rs - area) / 15;
    return asr(l, mid, ls, eps * .5, dep - 1, func) +
           asr(mid, r, rs, eps * .5, dep - 1, func);
  }

public:
  SimpsonSolver(double eps, int least_dep)
    : eps__(eps), least_dep__(least_dep) {}
  template <typename Func>
  double operator()(double l, double r, Func &&func) const {
    return asr(l, r, simpson(l, r, func), eps__, least_dep__, func);
  }
} simpson_solver(1e-6, 8);
namespace FFT {
using CP = std::complex<double>;
const double PI = acos(-1.0);
size_t n = 0;
std::vector<size_t> rev;
void init(size_t m) {
  if (n > m) return;
  n = 1;
  int k = 0;
  while (n <= m) {
    n <<= 1;
    ++k;
  }
  rev.resize(n);
  for (int i = 0; i < n; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
}
void dft(std::vector<CP> &a, int op) {
  for (int i = 0; i < n; ++i)
    if (rev[i] > i) std::swap(a[rev[i]], a[i]);
  for (int i = 1; i < n; i <<= 1) {
    CP now(std::cos(PI / i), op * std::sin(PI / i));
    for (int j = 0, p = (i << 1); j < n; j += p) {
      CP w(1, 0);
      for (int k = 0; k < i; ++k, w = w * now) {
        CP x = a[j + k], y = a[j + k + i] * w;
        a[j + k] = x + y;
        a[j + k + i] = x - y;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < n; ++i) a[i] = {a[i].real() / n, a[i].imag() / n};
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
std::vector<double> qpow(std::vector<double> a, uint64_t b) {
  std::vector<double> res{1};
  for (; b; b >>= 1, a = conv(a, a))
    if (b & 1) res = conv(res, a);
  return res;
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int x, y;
  cin >> x >> y;
  if (x * y < N) {
    vector<double> f = qpow(vector<double>(x, 1. / x), y);
    for_(i, 1, f.size() - 1) f[i] += f[i - 1];
    for_(i, 1, 10, a, b) {
      cin >> a >> b;
      cout << f[b] - (a ? f[a - 1] : 0) << '\n';
    }
  } else {
    const double ymu = (x - 1) * .5 * y,
                 ystdi = 1. / sqrt((x * x - 1) / 12. * y);
    auto norm = [ymu, ystdi](double x) -> double { return (x - ymu) * ystdi; };
    auto f = [](double x) -> double {
      return exp(-x * x * .5) / sqrt(2 * acos(-1.));
    };
    for_(i, 1, 10, a, b) {
      cin >> a >> b;
      cout << simpson_solver(norm(a), norm(b), f) << '\n';
    }
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  std::cout << std::fixed << std::setprecision(12);
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
