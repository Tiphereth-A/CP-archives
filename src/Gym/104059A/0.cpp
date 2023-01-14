#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
template <typename... Ts>
void dec(Ts &...x) {
  ((--x), ...);
}
template <typename... Ts>
void inc(Ts &...x) {
  ((++x), ...);
}
using namespace std;
void solve(int t_ = 0) {
  i64 a, b;
  cin >> a >> b;
  if (a > b) swap(a, b);
  --a;
  --b;
  i64 g = gcd(a, b);
  if (g == 1) {
    cout << (a != b) + 1 << '\n';
    return;
  }
  i64 cnt = 1 + (a != b);
  for (i64 i = 1; i < a; ++i)
    if (i64 j = sqrtl(a * a - i * i); a * a == i * i + j * j)
      cnt += 1 + (a != b);
  cout << cnt << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
