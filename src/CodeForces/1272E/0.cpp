#include <bits/extc++.h>
using namespace std;
template <typename Tp>
using vc = std::vector<Tp>;
template <typename Tp>
using vvc = std::vector<std::vector<Tp>>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define foreach_ref_(i, container) for (auto &i : (container))
#define foreach_cref_(i, container) for (const auto &i : (container))
#define all_(a) (a).begin(), (a).end()
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
#define read_container_(type, name, size) \
  type name(size);                        \
  foreach_ref_(i, name) std::cin >> i;
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
vvc<int> g;
auto solve([[maybe_unused]] int t_) -> void {
  read_var_(int, n);
  read_container_(vc<int>, v, n);
  g.resize(n);
  for_(i, 0, n - 1) {
    if (i - v[i] >= 0) g[i - v[i]].push_back(i);
    if (i + v[i] < n) g[i + v[i]].push_back(i);
  }
  vc<int> odd(n), even(n);
  transform(
    all_(v), odd.begin(), [](const int &x) -> int { return x % 2 - 1; });
  transform(
    all_(v), even.begin(), [](const int &x) -> int { return -(x % 2); });
  queue<int> q;
#define __(type)                                  \
  for_(i, 0, n - 1)                               \
    if (~type[i]) q.push(i);                      \
  while (!q.empty()) {                            \
    auto &&now = q.front();                       \
    foreach_cref_(v, g[now])                      \
      if (!~type[v] || type[v] > type[now] + 1) { \
        type[v] = type[now] + 1;                  \
        q.push(v);                                \
      }                                           \
    q.pop();                                      \
  }
  __(odd)
  __(even)
#undef __
  for_(i, 0, n - 1) cout << ((v[i] & 1) ? even : odd)[i] << " \n"[i == n - 1];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
