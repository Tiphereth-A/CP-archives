#include <bits/stdc++.h>
using i64 = int64_t;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 r;
  cin >> r;
  i64 ans = 1;
  for_(i, 2, (i64)sqrt(r), cnt) {
    if (i > r) break;
    if (r % i) continue;
    cnt = 0;
    while (r % i == 0) {
      r /= i;
      ++cnt;
    }
    if (i % 4 > 1) continue;
    ans *= cnt * 2 + 1;
  }
  if (r > 1 && r % 4 == 1) ans *= 3;
  cout << ans * 4;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(0);
  return 0;
}
