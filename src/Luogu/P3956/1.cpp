#include <bits/stdc++.h>
int m, n, a[105][105], f[105][105], ans = 0x3fffffff;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
void dfs(int x, int y, int sum, bool magic) {
  if (x < 1 || y < 1 || x > m || y > m) return;
  if (!a[x][y]) return;
  if (sum >= f[x][y]) return;
  f[x][y] = sum;
  if (x == m && y == m) {
    if (ans > sum) ans = sum;
    return;
  }
  for (int i = 0; i < 4; ++i) {
    int xx = x + dx[i], yy = y + dy[i];
    if (a[xx][yy]) {
      if (a[xx][yy] == a[x][y]) dfs(xx, yy, sum, false);
      else dfs(xx, yy, sum + 1, false);
    } else if (!a[xx][yy] && !magic) {
      a[xx][yy] = a[x][y];
      dfs(xx, yy, sum + 2, true);
      a[xx][yy] = 0;
    }
  }
}
int main() {
  memset(f, 0x7f, sizeof(f));
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= n; ++i) {
    int x, y, color;
    scanf("%d%d%d", &x, &y, &color);
    a[x][y] = color + 1;
  }
  dfs(1, 1, 0, false);
  if (ans == 0x3fffffff) ans = -1;
  printf("%d", ans);
  return 0;
}
