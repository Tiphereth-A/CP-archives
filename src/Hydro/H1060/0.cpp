#include <bits/stdc++.h>
using namespace std;
using i128 = __int128_t;
const int OFFSET = 1;
const int N = 5e7 + OFFSET, P = 6002268 + OFFSET;
const int MOD = 1e9 + 7;
bool vis[N];
int f[N];
int prime[P], cnt_prime;
constexpr i128 pow6(int k) {
  k = (1ll * k * k) % MOD;
  return (i128)k * k * k % MOD;
}
void init_prime(const int &n = N - 1) {
  f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) f[prime[++cnt_prime] = i] = pow6(i) - 1;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      f[i * prime[j]] = f[i] * pow6(prime[j]) % MOD;
      if (f[i * prime[j]] >= MOD) f[i * prime[j]] -= MOD;
      if (i % prime[j] == 0) break;
      if ((f[i * prime[j]] -= f[i]) < 0) f[i * prime[j]] += MOD;
    }
  }
  for (int i = 2; i <= n; ++i)
    if ((f[i] += f[i - 1]) >= MOD) f[i] -= MOD;
}
auto __STATIC__ = []() {
  init_prime();
  return 0.0;
}();
constexpr int F(const int x,
                const int d,
                const int r,
                const int e,
                const int a,
                const int m) {
  return (i128)(d / x) * (r / x) * (e / x) * (a / x) % MOD * (m / x) % MOD;
}
int _m;
i128 ans;
int d, r, e, a, m;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    cin >> d >> r >> e >> a >> m;
    _m = min({d, r, e, a, m});
    ans = 0;
    for (int _l = 1, _r; _l <= _m; _l = _r + 1) {
      _r = min(
        {d / (d / _l), r / (r / _l), e / (e / _l), a / (a / _l), m / (m / _l)});
      ans += 1ll * (f[_r] - f[_l - 1] + MOD) * F(_l, d, r, e, a, m) % MOD;
    }
    cout << (int)(ans % MOD) << '\n';
  }
  return 0;
}
