#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 1e7, mod = 20101009;
int prime[N / 10 + OFFSET], cnt_prime;
bool vis[N + OFFSET];
i64 mu[N + OFFSET], sum[N + OFFSET];
void init(int n = N) {
  mu[1] = 1;
  _for(i, 2, n) {
    if (!vis[i]) mu[prime[++cnt_prime] = i] = -1;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
      mu[i * prime[j]] = -mu[i];
    }
  }
  _for(i, 1, n) sum[i] = (sum[i - 1] + 1ll * i * i % mod * (mu[i] + mod)) % mod;
}
i64 f(i64 x, i64 y) {
  return x * (x + 1) / 2 % mod * (y * (y + 1) / 2 % mod) % mod;
}
int main() {
  int n, m;
  cin >> n >> m;
  init(min(m, n));
  i64 res = 0;
  for (int l = 1, r; l <= min(m, n); l = r + 1) {
    r = min(n / (n / l), m / (m / l));
    int res2 = 0, nl = n / l, ml = m / l;
    for (int l2 = 1, r2; l2 <= min(nl, ml); l2 = r2 + 1) {
      r2 = min(nl / (nl / l2), ml / (ml / l2));
      (res2 += (sum[r2] - sum[l2 - 1] + mod) * f(nl / l2, ml / l2) % mod) %=
        mod;
    }
    (res += (r - l + 1ll) * (l + r) / 2 % mod * res2 % mod) %= mod;
  }
  cout << res;
}
