#include <bits/stdc++.h>
using namespace std;
int n, m, sx[3], sy[3], cnt, ans;
char g[208][99];
int dis[208][99];
int dx[5] = {0, 2, 0, -2};
int dy[5] = {2, 0, -2, 0};
int rx[5] = {0, 1, 0, -1};
int ry[5] = {1, 0, -1, 0};
struct node {
  int x, y, sum;
} temp, now;
queue<node> Q;
bool vis[208][99];
void bfs(int num) {
  memset(vis, 0, sizeof(vis));
  while (!Q.empty()) Q.pop();
  vis[sx[num]][sy[num]] = 1;
  temp.sum = 0, temp.x = sx[num], temp.y = sy[num];
  Q.push(temp);
  while (!Q.empty()) {
    now = Q.front();
    int x = now.x, y = now.y, s = now.sum;
    Q.pop();
    dis[x][y] = min(s, dis[x][y]);
    for (int i = 0; i < 4; i++) {
      int xx = dx[i] + x, yy = dy[i] + y;
      int zx = rx[i] + x, zy = ry[i] + y;
      if (xx <= 2 * n + 1 && xx > 0 && yy <= 2 * m + 1 && yy > 0 &&
          !vis[xx][yy] && g[xx][yy] == ' ' && g[zx][zy] == ' ' &&
          (x != sx[num] || y != sy[num])) {
        vis[xx][yy] = 1;
        temp.x = xx, temp.y = yy, temp.sum = s + 1;
        Q.push(temp);
      }
      if (zx <= 2 * n + 1 && zy <= 2 * m + 1 && zx > 0 && zy > 0 &&
          !vis[zx][zy] && g[zx][zy] == ' ' && x == sx[num] && y == sy[num]) {
        vis[zx][zy] = 1;
        temp.x = zx, temp.y = zy, temp.sum = s + 1;
        Q.push(temp);
      }
    }
  }
}
int main() {
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= 2 * n + 1; i++)
    for (int j = 1; j <= 2 * m + 1; j++) dis[i][j] = INT_MAX;
  fgets(g[0], 89, stdin);
  for (int i = 1; i <= 2 * n + 1; i++) {
    fgets(g[i] + 1, 89, stdin);
    for (int j = 1; j <= 2 * m + 1; j++) {
      if (i == 1 || j == 1 || i == 2 * n + 1 || j == 2 * m + 1)
        if (g[i][j] == ' ') {
          sx[++cnt] = i;
          sy[cnt] = j;
        }
    }
  }
  bfs(1);
  bfs(2);
  for (int i = 1; i <= 2 * n + 1; i++)
    for (int j = 1; j <= 2 * m + 1; j++)
      if (dis[i][j] != INT_MAX) ans = max(ans, dis[i][j]);
  printf("%d", ans);
}
