#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 2, mod = 104857601;
i64 qpow(i64 a, i64 b) {
  i64 res = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) res = res * a % mod;
  return res;
}
i64 inv(i64 a) { return qpow(a, mod - 2); }
int prime[N / 10], cnt;
bool vis[N];
int smu[N];
void seive(int n = N - 2) {
  smu[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) smu[prime[++cnt] = i] = -1;
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
      smu[i * prime[j]] = -smu[i];
    }
  }
  for (int i = 2; i <= n; ++i) smu[i] += smu[i - 1];
}
int main() {
  seive();
  int n;
  cin >> n;
  i64 ans = 1;
  for (int i = 2; i <= n; ++i) (ans *= i) %= mod;
  ans = qpow(ans, 2 * n);
  i64 fl = 1, fr = 1;
  int il = 1, ir = 1;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    i64 exp = 0;
    for (int l2 = 1, r2, n2 = n / l; l2 <= n2; l2 = r2 + 1) {
      r2 = n2 / (n2 / l2);
      exp += 1ll * (n2 / l2) * (n2 / l2) % (mod - 1) *
             (smu[r2] - smu[l2 - 1] + mod - 1) % (mod - 1);
      exp %= mod - 1;
    }
    while (ir <= r) (fr *= ir++) %= mod;
    while (il < l) (fl *= il++) %= mod;
    ans *= qpow(inv(fr) * fl % mod, exp * 2 % (mod - 1));
    ans %= mod;
  }
  cout << ans << endl;
  return 0;
}
