#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define rfor_(i, r, l, vars...)                                           \
  for (std::make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vars; \
       i >= i##end;                                                       \
       --i)
#define foreach_ref_(i, container) for (auto &i : container)
#define foreach_riter_(it, container) \
  for (auto it = (container).rbegin(); it != (container).rend(); ++it)
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  std::cin >> n;
  vector<int> a(n);
  foreach_ref_(i, a) std::cin >> i;
  vector<int> idx(n);
  map<int, int> f;
  int ans = 0, x = 0;
  for_(i, 0, n - 1)
    if (ans < (f[a[i]] = f[a[i] - 1] + 1)) ans = f[x = a[i]];
  cout << ans << '\n';
  vector<int> tmp;
  rfor_(i, n - 1, 0)
    if (a[i] == x) {
      tmp.push_back(i + 1);
      --x;
    }
  foreach_riter_(it, tmp) cout << *it << " \n"[it == tmp.rend()];
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
