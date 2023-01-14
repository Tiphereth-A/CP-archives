#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 2e7 + 5, mod = 1e9 + 7;
int prime[N / 10], cnt;
bool vis[N];
int sd[N], pk[N];
void seive(int n = N - 1) {
  sd[1] = pk[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      pk[cnt] = (i64)i * i % mod;
      sd[i] = (pk[cnt] - 1 + mod) % mod;
    }
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      sd[i * prime[j]] = (i64)sd[i] * pk[j] % mod;
      if (i % prime[j] == 0) break;
      (sd[i * prime[j]] += mod - sd[i]) %= mod;
    }
  }
  for (int i = 2; i <= n; ++i) (sd[i] += sd[i - 1]) %= mod;
}
i64 calc(i64 n, i64 m) {
  if (n > m) swap(m, n);
  i64 ans = 0;
  for (i64 l = 1, r; l <= n; l = r + 1) {
    r = min(n / (n / l), m / (m / l));
    (ans += (i64)(n / l) * (m / l) % mod * (sd[r] - sd[l - 1] + mod) % mod) %=
      mod;
  }
  return ans;
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 n, m, p;
  cin >> n >> m >> p;
  cout << (calc(n, m) * p % mod + calc(m, p) * n % mod + calc(p, n) * m % mod) %
            mod
       << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  seive();
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
