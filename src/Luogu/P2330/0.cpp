#include <bits/stdc++.h>
using namespace std;
int g[305][305];
int minn[305];
bool vis[305];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 1, a, b, c; i <= m; ++i) {
    cin >> a >> b >> c;
    g[a][b] = g[b][a] = c;
  }
  memset(minn, 0x3f, sizeof(minn));
  minn[1] = 0;
  for (int i = 1, k; i <= n; ++i) {
    k = 0;
    for (int j = 1; j <= n; j++)
      if (!vis[j] && (minn[j] < minn[k])) k = j;
    vis[k] = 1;
    for (int j = 1; j <= n; j++)
      if (!vis[j] && g[k][j] != 0 && g[k][j] < minn[j]) minn[j] = g[k][j];
  }
  int ans = -1;
  for (int i = 1; i <= n; ++i)
    if (minn[i] > ans) ans = minn[i];
  cout << n - 1 << ' ' << ans;
  return 0;
}
