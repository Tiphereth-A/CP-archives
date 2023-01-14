#include <bits/stdc++.h>
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
int m, n, a[105][105], f[105][105], ans = 0x3f3f3f3f;
void dfs(int x = 1, int y = 1, int sum = 0, bool magic = 0) {
  if (x < 1 || y < 1 || x > m || y > m || !a[x][y] || sum >= f[x][y]) return;
  f[x][y] = sum;
  if (x == m && y == m) {
    if (ans > sum) ans = sum;
    return;
  }
  for (int i = 0; i < 4; ++i) {
    int xx = x + dx[i], yy = y + dy[i];
    if (a[xx][yy]) dfs(xx, yy, sum + (a[xx][yy] != a[x][y]), false);
    else if (!a[xx][yy] && !magic) {
      a[xx][yy] = a[x][y];
      dfs(xx, yy, sum + 2, true);
      a[xx][yy] = 0;
    }
  }
}
int main() {
  memset(f, 0x3f, sizeof(f));
  scanf("%d%d", &m, &n);
  for (int i = 1, x, y, color; i <= n; ++i) {
    scanf("%d%d%d", &x, &y, &color);
    a[x][y] = color + 1;
  }
  dfs();
  printf("%d", ans == 0x3f3f3f3f ? -1 : ans);
  return 0;
}
