#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 a, b;
  cin >> a >> b;
  i64 _ = abs(a - b);
  i64 k = 0, mina = lcm(a, b);
  for (i64 g = 1, s_ = sqrtl(_); g <= s_; ++g) {
    if (_ % g) continue;
    i64 k_ = g - b % g, ma_ = (a + k_) * (b + k_) / gcd(_, b + k_);
    if (ma_ < mina) {
      mina = ma_;
      k = k_;
    }
    if (g == _ / g) break;
    g = _ / g;
    k_ = g - b % g, ma_ = (a + k_) * (b + k_) / gcd(_, b + k_);
    if (ma_ < mina) {
      mina = ma_;
      k = k_;
    }
    g = _ / g;
  }
  cout << k << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
