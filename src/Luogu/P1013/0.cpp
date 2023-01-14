#include <bits/extc++.h>
using namespace std;
template <typename Tp>
using vc = std::vector<Tp>;
template <typename Tp>
using vvc = std::vector<std::vector<Tp>>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define all_(a) (a).begin(), (a).end()
#define run_exec_(expressions, after_process) \
  {                                           \
    expressions;                              \
    after_process;                            \
  }
#define run_return_void_(expressions) run_exec_(expressions, return)
#define run_break_(expressions) run_exec_(expressions, break)
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
  bool f = true;
  if (&os == &std::cerr) os << "[";
  if (&os == &std::cerr)
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
  else
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  if (&os == &std::cerr) os << "]";
  return os;
}
bool valid(const vvc<string> &s, const vc<int> &p, int n) {
  map<string, int> table;
  for_(i, 1, n - 1) table[s[0][i]] = p[i - 1];
  for_(i, 1, n - 1)
    for_(j, 1, n - 1)
      table[s[0][i] + s[0][j]] = table[s[0][i]] * (n - 1) + table[s[0][j]];
  for_(i, 1, n - 1)
    for_(j, 1, n - 1)
      if (table[s[i][j]] != table[s[0][i]] + table[s[j][0]]) return false;
  return true;
}
auto solve([[maybe_unused]] int t_) -> void {
  read_var_(int, n);
  vvc<string> s(n, vc<string>(n));
  for_(i, 0, n - 1)
    for_(j, 0, n - 1) cin >> s[i][j];
  vc<int> p(n);
  iota(all_(p), 0);
  bool f = 0;
  do {
    if (valid(s, p, n)) run_break_(f = 1);
  } while (next_permutation(all_(p)));
  if (!f) run_return_void_(cout << "ERROR!");
  for_(i, 1, n - 1) cout << s[0][i] << '=' << p[i - 1] << " \n"[i == n - 1];
  cout << n - 1;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
