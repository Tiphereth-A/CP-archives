#include <bits/stdc++.h>
using namespace std;
using u32 = std::uint32_t;
using i64 = std::int64_t;
#define OPERATOR_OVERRIED_PAIR_(oper)                                       \
  template <typename Tp, typename Up>                                       \
  constexpr std::pair<Tp, Up> &operator oper##=(                            \
    std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) {                 \
    lhs.first oper## = rhs.first;                                           \
    lhs.second oper## = rhs.second;                                         \
    return lhs;                                                             \
  }                                                                         \
  template <typename Tp, typename Up>                                       \
  constexpr std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs,          \
                                            const std::pair<Tp, Up> &rhs) { \
    return lhs oper## = rhs;                                                \
  }
OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)
#undef OPERATOR_OVERRIED_PAIR_
template <typename Tp, typename Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define rfor_(i, r, l, vars...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vars; \
       i >= i##end;                                                  \
       --i)
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
template <class Tp>
auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
template <typename Tp>
auto discretization(Tp &var) -> Tp {
  Tp d__(var);
  std::sort(d__.begin(), d__.end());
  d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
  for (auto &i : var)
    i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
  return d__;
};
template <typename Tp>
auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  if (&os == &std::cerr) return os << "(" << p.first << ", " << p.second << ")";
  return os << p.first << " " << p.second;
}
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Container &x) {
  if (&os == &std::cerr) os << "[";
  if (&os == &std::cerr)
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
  else
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  if (&os == &std::cerr) os << "]";
  return os;
}
const u32 OFFSET = 5;
const u32 N = 5e5 + OFFSET;
const u32 MOD = 1e9 + 7;
i64 l[N], r[N];
i64 x[N], radius[N];
auto solve([[maybe_unused]] int t_) -> void {
  read_var_(i64, n);
  for_(i, 1, n) cin >> x[i] >> radius[i];
  iota(l, l + n + 1, 0);
  iota(r, r + n + 1, 0);
  for_(i, 2, n)
    while (l[i] > 1 && x[i] - x[l[i] - 1] <= radius[i]) {
      chkmax(radius[i], radius[l[i] - 1] - (x[i] - x[l[i] - 1]));
      l[i] = l[l[i] - 1];
    }
  rfor_(i, n - 1, 1)
    while (r[i] < n && x[r[i] + 1] - x[i] <= radius[i]) {
      chkmin(l[i], l[r[i] + 1]);
      r[i] = r[r[i] + 1];
    }
  i64 ans = 0;
  for_(i, 1, n) ans += i * (r[i] - l[i] + 1) % MOD;
  cout << ans % MOD;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
