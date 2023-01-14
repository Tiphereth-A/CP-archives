#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
using namespace std;
const int MOD = 998244353;
const int INV2 = (MOD + 1) / 2, INV3 = (MOD + 1) / 3;
void solve(int t_ = 0) {
  i64 n;
  cin >> n;
  auto calc = [](i64 a, i64 n) -> i64 {
    i64 ans = 0;
    for (i64 l = a, r, cnt = 1; l <= n; l = r + 1, ++cnt) {
      r = min(l * a - 1, n);
      (ans += cnt * ((r - l + 1) % MOD) % MOD) %= MOD;
    }
    return ans * a % MOD;
  };
  auto f = [&](i64 x) {
    x %= MOD;
    return x * (x + 1) % MOD * INV2 % MOD * ((n * 3 + 2 - 2 * x) % MOD) % MOD *
           INV3 % MOD;
  };
  i64 ans = 0;
  for_(i, 2, sqrtl(n)) (ans += calc(i, n)) %= MOD;
  cout << (ans + (f(n) + MOD - f((i64)floor(sqrtl(n))))) % MOD << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
