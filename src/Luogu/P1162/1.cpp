#include <bits/stdc++.h>
#define MAXN 33
#define _for(i, m, n) for (int i = m; i <= n; i++)
using namespace std;
int f[MAXN][MAXN], n;
void dfs(int x, int y) {
  f[x][y] = 2;
  if (x > 0 && y + 1 > 0 && x <= n && y + 1 <= n && f[x][y + 1] == 0)
    dfs(x, y + 1);
  if (x > 0 && y - 1 > 0 && x <= n && y - 1 <= n && f[x][y - 1] == 0)
    dfs(x, y - 1);
  if (x + 1 > 0 && y > 0 && x + 1 <= n && y <= n && f[x + 1][y] == 0)
    dfs(x + 1, y);
  if (x - 1 > 0 && y > 0 && x - 1 <= n && y <= n && f[x - 1][y] == 0)
    dfs(x - 1, y);
  return;
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
