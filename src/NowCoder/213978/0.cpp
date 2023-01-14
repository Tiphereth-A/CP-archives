#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
bool vis[N];
int mu[N], prime[N], cnt;
long long a[N], b[N], c[N];
int main() {
  int n;
  cin >> n;
  mu[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      mu[i * prime[j]] = 0;
      if (i % prime[j] == 0) break;
      mu[i * prime[j]] = -mu[i];
    }
  }
  for (int i = 1, _; i <= n; ++i) {
    _ = i;
    while (_) {
      a[i] += _ % 10;
      _ /= 10;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= sqrt(i); ++j)
      if (i % j == 0) {
        b[j] += i / j * a[i];
        c[j] += a[i];
        if (j != i / j) {
          b[i / j] += j * a[i];
          c[i / j] += a[i];
        }
      }
  }
  long long ans = 0;
  for (int i = 1; i <= n; ++i) ans += mu[i] * ((n / i + 1) * c[i] - b[i]);
  cout << ans;
  return 0;
}
