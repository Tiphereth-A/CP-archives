#include <bits/stdc++.h>
const int N = 405;
const int dx[] = {2, 2, 1, -1, -2, -2, 1, -1},
          dy[] = {1, -1, 2, 2, -1, 1, -2, -2};
int f[N][N];
int m, n;
void dfs(int x, int y, int step) {
  if (step > 200) return;
  f[x][y] = step;
  for (int i = 0; i < 8; ++i) {
    int xx = x + dx[i], yy = y + dy[i];
    if (xx > 0 && yy > 0 && yy <= m && xx <= n &&
        (f[xx][yy] == -1 || f[xx][yy] > step + 1))
      dfs(xx, yy, step + 1);
  }
}
int main() {
  int x, y;
  memset(f, 0xff, sizeof(f));
  std::cin >> n >> m >> x >> y;
  dfs(x, y, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) printf("%-5d", f[i][j]);
    printf("\n");
  }
  return 0;
}
