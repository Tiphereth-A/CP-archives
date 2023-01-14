#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 1e6 + 25;
const long long MOD = 666623333;
long long prime[N + 5], cnt;
bool vis[N + 5];
long long l, r, a[N + 5], b[N + 5], ans;
int main() {
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
  for (int i = 0; i < len; ++i) {
    if (b[i] > 1) (a[i] /= b[i]) *= b[i] - 1;
    (ans += l + i - a[i]) %= MOD;
  }
  cout << ans;
  return 0;
}
