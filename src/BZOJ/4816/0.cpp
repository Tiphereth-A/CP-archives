#include <algorithm>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e6 + 5, mod = 1e9 + 7;
i64 qpow(i64 a, i64 b) {
  i64 res = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) res = res * a % mod;
  return res;
}
i64 inv(i64 a) { return qpow(a, mod - 2); }
int prime[N], cnt;
bool vis[N];
i64 mu[N], f[N], inv_f[N], F[N];
void seive(int n = N - 5) {
  mu[1] = f[1] = inv_f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
      mu[i * prime[j]] = -mu[i];
    }
  }
  for (int i = 2; i <= n; ++i)
    inv_f[i] = inv(f[i] = (f[i - 1] + f[i - 2]) % mod);
  for (int i = 0; i <= n; ++i) F[i] = 1;
  for (int i = 1; i <= n; ++i) {
    if (!mu[i]) continue;
    for (int j = i; j <= n; j += i) {
      (F[j] *= mu[i] == 1 ? f[j / i] : inv_f[j / i]) %= mod;
    }
  }
  for (int i = 1; i <= n; ++i) (F[i] *= F[i - 1]) %= mod;
}
int main() {
  seive();
  int t;
  cin >> t;
  while (t--) {
    int m, n;
    cin >> m >> n;
    if (m > n) swap(m, n);
    i64 ans = 1;
    for (int l = 1, r; l <= m; l = r + 1) {
      r = min(n / (n / l), m / (m / l));
      (ans *= qpow(F[r] * inv(F[l - 1]) % mod,
                   1ll * (n / l) * (m / l) % (mod - 1))) %= mod;
    }
    cout << ans << endl;
  }
}
