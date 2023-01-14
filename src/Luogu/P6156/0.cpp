#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 5, mod = 998244353;
i64 qpow(i64 a, i64 b) {
  i64 res = 1;
  a %= mod;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) res = res * a % mod;
  return res;
}
int prime[N], cnt;
bool vis[N];
i64 sf[N], sik[N];
void seive(int n, i64 k) {
  sf[1] = sik[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      sf[i] = i - 1;
      sik[i] = qpow(i, k);
    }
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      sik[i * prime[j]] = sik[i] * sik[prime[j]] % mod;
      sf[i * prime[j]] = sf[i] * (prime[j] - 1) % mod;
      if (i % prime[j] == 0) {
        sf[i * prime[j]] = ((i / prime[j]) % prime[j]) ?
                             (mod - prime[j]) * sf[i / prime[j]] % mod :
                             0;
        break;
      }
    }
  }
  for (int i = 2; i <= n; ++i) {
    sf[i] = (sf[i - 1] + sik[i] * sf[i] % mod) % mod;
    (sik[i] += sik[i - 1]) %= mod;
  }
  for (int i = 2; i <= n; ++i) (sik[i] += sik[i - 1]) %= mod;
}
i64 s(int n) { return ((sik[n * 2] - 2 * sik[n] % mod) % mod + mod) % mod; }
int main() {
  int n;
  i64 k;
  cin >> n >> k;
  k %= mod - 1;
  seive(min(n * 2, N - 5), k);
  i64 ans = 0;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    (ans += (((sf[r] - sf[l - 1]) % mod + mod) % mod) * s(n / l)) %= mod;
  }
  cout << ans;
}
