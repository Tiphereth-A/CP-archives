#include <bits/stdc++.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))
int r, c, f[105][105], g[105][105], MAXN, t, ans;
short dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int dfs(int x, int y) {
  if (g[x][y]) return g[x][y];
  int tmp = 1;
  for (int i = 0; i < 4; i++) {
    int xx = x + dx[i], yy = y + dy[i];
    if (xx > 0 && xx <= r && yy > 0 && yy <= c && f[xx][yy] < f[x][y])
      tmp = max(tmp, dfs(xx, yy) + 1);
  }
  g[x][y] = tmp;
  return tmp;
}
int main() {
  scanf("%d%d", &r, &c);
  for (int i = 1; i <= r; i++)
    for (int j = 1; j <= c; j++) scanf("%d", &f[i][j]);
  for (int i = 1; i <= r; i++)
    for (int j = 1; j <= c; j++) {
      t = dfs(i, j);
      g[i][j] = t;
      ans = max(ans, g[i][j]);
    }
  printf("%d", ans);
  return 0;
}
