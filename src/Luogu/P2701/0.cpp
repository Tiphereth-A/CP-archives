#include <bits/stdc++.h>
using namespace std;
bool vis[1005][1005];
int f[1005][1005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    vis[x][y] = 1;
  }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (!vis[i][j])
        f[i][j] = min({f[i][j - 1], f[i - 1][j], f[i - 1][j - 1]}) + 1;
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) ans = max(ans, f[i][j]);
  cout << ans;
  return 0;
}
