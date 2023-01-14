#include <bits/stdc++.h>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define rfor_(i, r, l, v...) for (ll i = (r), i##e = (l), ##v; i >= i##e; --i)
#define Rep for_
#define rep rfor_
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
const int MOD = 998244353;
#define int long long
void solve(int t_ = 0) {
  int n, m, k;
  cin >> n >> m >> k;
  if (k == 0) return (void)(cout << (m == 0 ? 1 : 0));
  vector<int> fac(n + 1), inv(n + 1);
  auto KSM = [&](int x, int p) -> int {
    int ret = 1;
    while (p) {
      if (p & 1) ret = ret * x % MOD;
      x = x * x % MOD, p >>= 1;
    }
    return ret;
  };
  fac[0] = 1;
  Rep(i, 1, n) fac[i] = fac[i - 1] * i % MOD;
  inv[n] = KSM(fac[n], MOD - 2);
  rep(i, n - 1, 0) inv[i] = inv[i + 1] * (i + 1) % MOD;
  auto C = [&](int n, int m) -> int {
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
  };
  auto f = [&](int i, int k) -> int {
    return C(n - i * (k + 1), n - m) * C(n - m + 1, i) % MOD;
  };
  auto g = [&](int k) -> int {
    int ans = 0;
    Rep(i, 0, n) {
      if (i > n - m + 1 || n - i * (k + 1) < n - m) break;
      (ans += (i & 1 ? -1 : 1) * f(i, k)) %= MOD;
    }
    return ans;
  };
  cout << ((g(k) - g(k - 1) % MOD) + MOD) % MOD;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
