#include <bits/stdc++.h>
using namespace std;
const int N = 3010;
int g[N][N], vis[N];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    g[x][y] = g[y][x] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    if (vis[i]) continue;
    for (int j = i + 1; j <= n; ++j) {
      if (vis[j] || g[i][j]) continue;
      vis[i] = vis[j] = 1;
      break;
    }
  }
  for (int i = 1, tot = 0; i <= n && tot < n / 3; ++i) {
    if (vis[i]) continue;
    printf("%d%c", i, " \n"[++tot == n / 3]);
  }
  return 0;
}
