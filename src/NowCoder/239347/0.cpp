#include <bits/stdc++.h>
using namespace std;
using i64 = std::int64_t;
using i128 = __int128_t;
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define foreach_ref_(i, container) for (auto &i : (container))
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
#define read_container_(type, name, size) \
  type name(size);                        \
  foreach_ref_(i, name) std::cin >> i;
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Container &x) {
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
auto solve([[maybe_unused]] int t_) -> void {
  read_var_(i64, n);
  read_container_(vc<i64>, v, n);
  i128 sum = 0, sum2 = 0;
  for_(i, 0, n - 1) sum += v[i];
  for_(i, 0, n - 1) sum2 += v[i] * (i + 1);
  long double a =
    1.l * (2 * sum2 - (n + 1) * sum) / (n * (n + 1) / 2 * (n - 1) / 3);
  long double b = 1.l * sum / n - a * (n + 1) / 2;
  long double res = 0;
  for_(i, 0, n - 1) {
    long double _ = 1.l * v[i] - a * (i + 1) - b;
    res += _ * _;
  }
  cout << res << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  cout << fixed << setprecision(15);
  int t_;
  std::cin >> t_;
  for (i_ = 1; i_ <= t_; ++i_) solve(i_);
  return 0;
}
