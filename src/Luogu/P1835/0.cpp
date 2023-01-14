#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
i64 prime[N], cnt;
bool vis[N];
int main() {
  i64 l, r;
  cin >> l >> r;
  if (l == 1) l = 2;
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= cnt; ++i) {
    for (i64 j = max((i64)ceil(1.0 * l / prime[i]) * prime[i], 2 * prime[i]);
         j <= r;
         j += prime[i])
      vis[j - l] = 1;
  }
  int ans = 0;
  for (int i = 0; i <= r - l; ++i) ans += !vis[i];
  cout << ans;
  return 0;
}
