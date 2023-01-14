#include <bits/stdc++.h>
#define _for(i, m, n) for (int i = m; i <= n; i++)
int f[33][33], n;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
void dfs(int x, int y) {
  f[x][y] = 2;
  _for(i, 0, 3) {
    int xx = x + dx[i], yy = y + dy[i];
    if (xx > 0 && yy > 0 && xx <= n && yy <= n && !f[xx][yy]) dfs(xx, yy);
  }
}
int main() {
  int x = 0, y = 0;
  scanf("%d", &n);
  _for(i, 1, n)
    _for(j, 1, n) {
      scanf("%d", &f[i][j]);
      if (f[i][j] && x == 0) {
        x = i + 1;
        y = j + 1;
      }
    }
  dfs(x, y);
  _for(i, 1, n) {
    _for(j, 1, n) printf("%d ", f[i][j]);
    printf("\n");
  }
  return 0;
}
