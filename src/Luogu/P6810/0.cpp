#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
int tau[N] = {0, 1}, pfac_num[N];
int prime[N], cnt;
bool vis[N];
i64 a[N], b[N];
int main() {
  int n, m, p;
  cin >> n >> m >> p;
  for (int i = 2; i <= max(n, m); ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      tau[i] = 2;
      pfac_num[i] = 1;
    }
    for (int j = 1; j <= cnt && i * prime[j] <= max(n, m); ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) {
        tau[i * prime[j]] = tau[i] / (pfac_num[i] + 1) * (pfac_num[i] + 2);
        pfac_num[i * prime[j]] = pfac_num[i] + 1;
        break;
      }
      tau[i * prime[j]] = 2 * tau[i];
      pfac_num[i * prime[j]] = 1;
    }
  }
  for (int i = 1; i <= n; ++i) a[i] = tau[i];
  for (int i = 1; i <= m; ++i) b[i] = tau[i];
  for (int i = 1; i <= cnt; ++i)
    for (int j = n / prime[i]; j; --j) (a[j] += a[j * prime[i]]) %= p;
  for (int i = 1; i <= cnt; ++i)
    for (int j = m / prime[i]; j; --j) (b[j] += b[j * prime[i]]) %= p;
  i64 ans = 0;
  for (int i = 1; i <= min(n, m); ++i) (ans += a[i] * b[i]) %= p;
  cout << ans;
  return 0;
}
