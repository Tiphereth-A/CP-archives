#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 25, MOD = 666623333;
i64 prime[N], cnt;
bool vis[N];
i64 a[N], b[N];
int main() {
  i64 l, r;
  cin >> l >> r;
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
  int len = r - l + 1;
  for (int i = 0; i < len; ++i) a[i] = b[i] = l + i;
  for (int i = 1; i <= cnt; ++i) {
    int p = prime[i];
    if (p * p > r) break;
    for (int j = (p - l % p) % p; j < len; j += p) {
      (a[j] /= p) *= p - 1;
      while (b[j] % p == 0) b[j] /= p;
    }
  }
  i64 ans = 0;
  for (int i = 0; i < len; ++i) {
    if (b[i] > 1) (a[i] /= b[i]) *= b[i] - 1;
    (ans += l + i - a[i]) %= MOD;
  }
  cout << ans;
  return 0;
}
