#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 5, mod = 1e9 + 7;
i64 qpow(i64 a, i64 b) {
  i64 res = 1;
  a %= mod;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) res = res * a % mod;
  return res;
}
int prime[N], cnt;
bool vis[N];
i64 sd[N], pk[N];
void seive(int n, i64 k) {
  sd[1] = pk[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      pk[cnt] = qpow(i, k);
      sd[i] = (pk[cnt] - 1 + mod) % mod;
    }
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      sd[i * prime[j]] = sd[i] * pk[j] % mod;
      if (i % prime[j] == 0) break;
      (sd[i * prime[j]] += mod - sd[i]) %= mod;
    }
  }
  for (int i = 2; i <= n; ++i) (sd[i] += sd[i - 1]) %= mod;
}
int main() {
  int t;
  i64 k;
  cin >> t >> k;
  k %= mod - 1;
  seive(N - 5, k);
  while (t--) {
    int m, n;
    cin >> m >> n;
    if (n > m) swap(m, n);
    i64 ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
      r = min(n / (n / l), m / (m / l));
      (ans +=
       1ll * (n / l) * (m / l) % mod * (sd[r] - sd[l - 1] + mod) % mod) %= mod;
    }
    cout << ans << endl;
  }
}
