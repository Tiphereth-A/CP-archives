#include <bits/stdc++.h>
using ll = long long;
using namespace std;
constexpr int N = 3005;
int s[N][N], fact[N];
constexpr int MOD = 1e9 + 7;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  fact[0] = 1;
  for (int i = 1; i < N; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
  s[0][0] = 1;
  for (int i = 1; i < N; ++i)
    for (int j = 1; j <= i; ++j)
      s[i][j] = (s[i - 1][j - 1] + (ll)j * s[i - 1][j]) % MOD;
  for (int i = 1; i < N; ++i)
    for (int j = 1; j <= i; ++j) s[i][j] = (ll)s[i][j] * fact[j] % MOD;
  int t_ = 0;
  std::cin >> t_;
  while (t_--) {
    int n, m;
    cin >> n >> m;
    ll ans = 1;
    for (int i = 1; i <= n && i <= m; ++i)
      ans += (ll)(s[n][i] + s[n][i + 1]) * (ll)(s[m][i] + s[m][i + 1]) % MOD;
    cout << ans % MOD << '\n';
  }
  return 0;
}
