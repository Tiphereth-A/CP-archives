#include <bits/stdc++.h>
using namespace std;
int deg[25];
bool edge[25][25], vis[25];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    if (x == y) continue;
    if (edge[x][y]) continue;
    ++deg[x];
    ++deg[y];
    edge[x][y] = edge[y][x] = 1;
  }
  for (int i = 1, s, j, mn, e; i <= n; ++i) {
    memset(vis, 0, sizeof(vis));
    vis[s = i] = 1;
    for (j = 1; j < n; ++j) {
      mn = e = 0;
      for (int k = 1; k <= n; ++k)
        if ((edge[s][k] && !vis[k]) && (e == 0 || mn > deg[k])) mn = deg[e = k];
      if (e == 0) break;
      vis[s = e] = 1;
    }
    if (j == n) {
      cout << "Yes\n";
      return 0;
    }
  }
  cout << "No\n";
  return 0;
}
