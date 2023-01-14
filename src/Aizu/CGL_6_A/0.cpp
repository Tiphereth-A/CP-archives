#include <bits/stdc++.h>
template <class Tp>
using pi4 = std::tuple<Tp, Tp, Tp, Tp>;
template <class Tp>
using vc = std::vector<Tp>;
using i64 = int64_t;
using pi4i = pi4<int>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define all_(a) (a).begin(), (a).end()
#define run_exec_(expressions, post_process) \
  {                                          \
    expressions;                             \
    post_process;                            \
  }
#define run_continue_(expressions) run_exec_(expressions, continue)
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
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
  assert(check(ok));
  while (std::abs(ok - ng) > 1) {
    Tp x = (ng + ok) / 2;
    (check(x) ? ok : ng) = x;
  }
  return ok;
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
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  vc<pi4i> vp4;
  read_var_(int, n);
  for_(i, 1, n, ax, ay, bx, by) {
    cin >> ax >> ay >> bx >> by;
    if (ax > bx) swap(ax, bx);
    if (ay > by) swap(ay, by);
    if (ax == bx) run_continue_(vp4.emplace_back(ax, 0, ay, by));
    vp4.emplace_back(ax, -1, ay, 0);
    vp4.emplace_back(bx, 1, by, 0);
  }
  sort(all_(vp4));
  i64 ans = 0;
  set<int> s;
  for (auto &&x : vp4) {
    if (get<1>(x) == -1) run_continue_(s.insert(get<2>(x)));
    if (get<1>(x) == 1) run_continue_(s.erase(get<2>(x)));
    ans += distance(s.lower_bound(get<2>(x)), s.upper_bound(get<3>(x)));
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
