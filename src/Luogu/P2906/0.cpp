#include <bits/stdc++.h>
using namespace std;
using u32 = std::uint32_t;
using i64 = std::int64_t;
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
template <class Tp>
using pi = std::pair<Tp, Tp>;
template <class Tp>
using vc = std::vector<Tp>;
using pii64 = pi<i64>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define all_(a) (a).begin(), (a).end()
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
const u32 N = 5e5 + OFFSET;
const i64 INF64 = 0x3f3f3f3f3f3f3f3f;
i64 fa[N];
i64 find(i64 x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
bool merge(i64 x, i64 y) {
  return find(x) == find(y) ? false : fa[find(x)] = find(y), true;
}
auto solve([[maybe_unused]] int t_) -> void {
  i64 n, c;
  cin >> n >> c;
  iota(fa, fa + n + 1, 0);
  vc<pii64> vec;
  vec.reserve(n);
  for_(i, 1, n, x, y) {
    cin >> x >> y;
    vec.emplace_back(x + y, x - y);
  }
  sort(all_(vec));
  set<pii64> s;
  s.emplace(-INF64, -1);
  s.emplace(INF64, -1);
  s.emplace(vec[0].second, 0);
  for_(now, 1, n - 1, l = 0) {
    while (vec[now].first - vec[l].first > c) {
      s.erase(make_pair(vec[l].second, l));
      ++l;
    }
    auto it = s.lower_bound(make_pair(vec[now].second, 0));
    if (~it->second && it->first - vec[now].second <= c) merge(now, it->second);
    if (~(--it)->second && vec[now].second - it->first <= c)
      merge(now, it->second);
    s.emplace(vec[now].second, now);
  }
  vc<i64> cnt(n);
  i64 tot = 0, ans = 0;
  for_(i, 0, n - 1) {
    tot += (find(i) == i);
    chkmax(ans, ++cnt[find(i)]);
  }
  cout << tot << ' ' << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
