#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MOD = 998244353;
const int N = 1e7 + 5;
int inv[N], combs[N];
int n, m;
int sum_c(int l, int r) {
  return ((r <= n ? combs[r] : 0) + MOD - (l > 0 ? combs[l - 1] : 0)) % MOD;
}
#define FLIP1(l, r) (n - 1) - r, (n - 1) - l
#define FLIP2(l, r) (n + (m + 1) / 2 + 1) - r, (n + (m + 1) / 2 + 1) - l
int g(int, int);
int f(int l, int r) {
  if (r < 0) return 0;
  l = max(l, 0);
  r = min(r, (n - 1) / 2);
  return (sum_c(l, r) + MOD - g(FLIP2(l, r))) % MOD;
}
int g(int l, int r) {
  if (l > n) return 0;
  l = max(l, (n + 1 + (m + 1) / 2 + 1) / 2);
  r = min(r, n);
  return (sum_c(l, r) + MOD - f(FLIP1(l, r))) % MOD;
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  cin >> n >> m;
  inv[0] = inv[1] = combs[0] = 1;
  for (int i = 2; i <= n; ++i)
    inv[i] = (i64)(MOD - MOD / i) * inv[MOD % i] % MOD;
  for (int i = 1; i <= n; ++i)
    combs[i] = (i64)combs[i - 1] * inv[i] % MOD * (n - i + 1) % MOD;
  for (int i = 1; i <= n; ++i) (combs[i] += combs[i - 1]) %= MOD;
  int l = (n + 1) / 2, r = (n + 1 + (m + 1) / 2) / 2;
  i64 ans = sum_c(l, r);
  (ans += MOD - f(FLIP1(l, r))) %= MOD;
  (ans += MOD - g(FLIP2(l, r))) %= MOD;
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
