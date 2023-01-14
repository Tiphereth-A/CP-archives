#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
const int N = 1005;
const int M = 1e6 + 5;
int n, m, ans;
int map[N][N], res[N][N] = {0};
struct node {
  int x, y;
} p[M];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void dfs(int x, int y) {
  ans++;
  p[ans] = {x, y};
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
    _for(j, 1, ans) res[p[j].x][p[j].y] = ans;
    printf("%d\n", ans);
  }
  return 0;
}
