#include <bits/stdc++.h>
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
using vvc = std::vector<std::vector<Tp>>;
using i64 = int64_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define for_step_(i, l, r, s, vars...)                                    \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       i += s)
using namespace std;
const i64 MP[4][4] = {
  {0, 1, 4, 5}, {2, 3, 6, 7}, {8, 9, 12, 13}, {10, 11, 14, 15}};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 n, m;
  cin >> n >> m;
  i64 k = 0;
  while ((1 << k) < n || (1 << k) < m) k += 2;
  vvc<i64> a(1 << k, vc<i64>(1 << k));
  for_(i, 0, 3)
    for_(j, 0, 3) a[i][j] = MP[i][j];
  for_step_(kk, 4, k, 2) {
    i64 pre = 1 << (kk - 2), pre2 = pre * pre;
    for_(i, 0, (1 << kk) - 1)
      for_(j, 0, (1 << kk) - 1)
        a[i][j] = pre2 * MP[i / pre][j / pre] + a[i % pre][j % pre];
  }
  cout << n * m << '\n';
  for_(i, 0, n - 1)
    for_(j, 0, m - 1) cout << a[i][j] << " \n"[j == m - 1];
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t_ = 0;
  std::cin >> t_;
  for (int i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
