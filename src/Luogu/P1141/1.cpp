#include <bits/stdc++.h>
#define MAXN 1005
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
using namespace std;
int n, m, ans;
int map[MAXN][MAXN];
int res[MAXN][MAXN] = {0};
int p[1000005][2];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void dfs(int x, int y) {
  ans++;
  p[ans][0] = x;
  p[ans][1] = y;
  res[x][y] = 1;
  _for(i, 0, 3) {
    int xx = x + dir[i][0], yy = y + dir[i][1];
    if ((xx < 1) || (xx > n) || (yy < 1) || (yy > n) || (res[xx][yy] > 0) ||
        (map[xx][yy] == map[x][y]))
      continue;
    dfs(xx, yy);
  }
}
int main() {
  scanf("%d %d", &n, &m);
  _for(i, 1, n)
    _for(j, 1, n) scanf("%1d", &map[i][j]);
  _for(i, 1, m) {
    ans = 0;
    int x, y;
    scanf("%d %d", &x, &y);
    if (res[x][y]) {
      printf("%d\n", res[x][y]);
      continue;
    }
    dfs(x, y);
    _for(j, 1, ans) res[p[j][0]][p[j][1]] = ans;
    printf("%d\n", ans);
  }
  return 0;
}
