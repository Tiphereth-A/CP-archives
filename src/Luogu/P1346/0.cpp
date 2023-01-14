#include <bits/stdc++.h>
using namespace std;
using i32 = std::int32_t;
using u32 = std::uint32_t;
#define OPERATOR_OVERRIED_PAIR_(oper)                                         \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator oper##=(                              \
    std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) {                   \
    lhs.first oper## = rhs.first;                                             \
    lhs.second oper## = rhs.second;                                           \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs,            \
                                            const std::pair<Tp, Up> &rhs) {   \
    return lhs oper## = rhs;                                                  \
  }                                                                           \
  template <class Tp, class Up, class Vp>                                     \
  constexpr std::tuple<Tp, Up, Vp> &operator oper##=(                         \
    std::tuple<Tp, Up, Vp> &lhs, const std::tuple<Tp, Up, Vp> &rhs) {         \
    std::get<0>(lhs) oper## = std::get<0>(rhs);                               \
    std::get<1>(lhs) oper## = std::get<1>(rhs);                               \
    std::get<2>(lhs) oper## = std::get<2>(rhs);                               \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up, class Vp>                                     \
  constexpr std::tuple<Tp, Up, Vp> operator oper(                             \
    std::tuple<Tp, Up, Vp> lhs, const std::tuple<Tp, Up, Vp> &rhs) {          \
    return lhs oper## = rhs;                                                  \
  }                                                                           \
  template <class Tp, class Up, class Vp, class Wp>                           \
  constexpr std::tuple<Tp, Up, Vp, Wp> &operator oper##=(                     \
    std::tuple<Tp, Up, Vp, Wp> &lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) { \
    std::get<0>(lhs) oper## = std::get<0>(rhs);                               \
    std::get<1>(lhs) oper## = std::get<1>(rhs);                               \
    std::get<2>(lhs) oper## = std::get<2>(rhs);                               \
    std::get<3>(lhs) oper## = std::get<3>(rhs);                               \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up, class Vp, class Wp>                           \
  constexpr std::tuple<Tp, Up, Vp, Wp> operator oper(                         \
    std::tuple<Tp, Up, Vp, Wp> lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) {  \
    return lhs oper## = rhs;                                                  \
  }
OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)
#undef OPERATOR_OVERRIED_PAIR_
template <class Ch, class Tr, class Tp, class Up>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Ch, class Tr, class Tp, class Up>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::tuple<Tp, Up, Vp> &p) {
  return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::tuple<Tp, Up, Vp> &p) {
  return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::tuple<Tp, Up, Vp, Wp> &p) {
  return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p) >>
         std::get<3>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::tuple<Tp, Up, Vp, Wp> &p) {
  return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p)
            << ' ' << std::get<3>(p);
}
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
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
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Container &x) {
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
const u32 OFFSET = 5;
const u32 N = 100 + OFFSET;
const i32 INF = 0x3f3f3f3f;
template <size_t N, class Tp>
class FloydSolver {
private:
  size_t n;
  Tp spath[N][N];

public:
  using self = FloydSolver<N, Tp>;
  explicit FloydSolver(size_t _n = N - 1): n(_n) {}
  self &resize(size_t _n) {
    n = _n;
    return *this;
  }
  self &init() {
    memset(spath, 0x3f, sizeof(spath));
    for (size_t i = 0; i <= n; ++i) spath[i][i] = 0;
    return *this;
  }
  self &addedge(size_t from, size_t to, Tp w = 1) {
    spath[from][to] = w;
    return *this;
  }
  self &floyd() {
    for (size_t k = 0; k <= n; ++k)
      for (size_t i = 0; i <= n; ++i)
        for (size_t j = 0; j <= n; ++j)
          if (spath[i][k] + spath[k][j] < spath[i][j])
            spath[i][j] = spath[i][k] + spath[k][j];
    return *this;
  }
  const Tp &query(size_t from, size_t to) { return spath[from][to]; }
};
FloydSolver<N, i32> fl;
auto solve([[maybe_unused]] int t_) -> void {
  int n, a, b;
  cin >> n >> a >> b;
  fl.resize(n).init();
  for_(i, 1, n, k) {
    cin >> k;
    for_(j, 1, k, x) {
      cin >> x;
      fl.addedge(i, x, j > 1);
    }
  }
  cout << (fl.floyd().query(a, b) == INF ? -1 : fl.query(a, b));
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
