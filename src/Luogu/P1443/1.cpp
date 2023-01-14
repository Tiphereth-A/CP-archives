#include <bits/stdc++.h>
#define MAXN 405
using namespace std;
int f[MAXN][MAXN];
int m, n;
void dfs(int x, int y, int step) {
  if (step > 200) return;
  f[x][y] = step;
  if (y + 1 <= m && x + 2 <= n &&
      (f[x + 2][y + 1] == -1 || f[x + 2][y + 1] > step + 1))
    dfs(x + 2, y + 1, step + 1);
  if (y - 1 > 0 && x + 2 <= n &&
      (f[x + 2][y - 1] == -1 || f[x + 2][y - 1] > step + 1))
    dfs(x + 2, y - 1, step + 1);
  if (y + 2 <= m && x + 1 <= n &&
      (f[x + 1][y + 2] == -1 || f[x + 1][y + 2] > step + 1))
    dfs(x + 1, y + 2, step + 1);
  if (y + 2 <= m && x - 1 > 0 &&
      (f[x - 1][y + 2] == -1 || f[x - 1][y + 2] > step + 1))
    dfs(x - 1, y + 2, step + 1);
  if (y - 1 > 0 && x - 2 > 0 &&
      (f[x - 2][y - 1] == -1 || f[x - 2][y - 1] > step + 1))
    dfs(x - 2, y - 1, step + 1);
  if (y + 1 <= m && x - 2 > 0 &&
      (f[x - 2][y + 1] == -1 || f[x - 2][y + 1] > step + 1))
    dfs(x - 2, y + 1, step + 1);
  if (y - 2 > 0 && x + 1 <= n &&
      (f[x + 1][y - 2] == -1 || f[x + 1][y - 2] > step + 1))
    dfs(x + 1, y - 2, step + 1);
  if (y - 2 > 0 && x - 1 > 0 &&
      (f[x - 1][y - 2] == -1 || f[x - 1][y - 2] > step + 1))
    dfs(x - 1, y - 2, step + 1);
  return;
}
int main() {
  int x, y;
  memset(f, -1, sizeof(f));
  cin >> n >> m >> x >> y;
  dfs(x, y, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) printf("%-5d", f[i][j]);
    printf("\n");
  }
  return 0;
}
