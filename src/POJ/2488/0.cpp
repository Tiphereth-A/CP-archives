#include <cstdio>
#include <cstring>
const int N = 27, dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1},
          dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
bool vis[N][N];
struct Step {
  char x, y;
} path[N];
bool success;
int kase, p, q;
void dfs(int x, int y, int num) {
  path[num].y = y + 'A' - 1;
  path[num].x = x + '0';
  if (num == p * q) {
    success = true;
    return;
  }
  for (int i = 0; i < 8; ++i) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (0 < nx && nx <= p && 0 < ny && ny <= q && !vis[nx][ny] && !success) {
      vis[nx][ny] = true;
      dfs(nx, ny, num + 1);
      vis[nx][ny] = false;
    }
  }
}
int main() {
  scanf("%d", &kase);
  for (int c = 1; c <= kase; ++c) {
    success = false;
    scanf("%d%d", &p, &q);
    memset(vis, false, sizeof(vis));
    vis[1][1] = true;
    dfs(1, 1, 1);
    printf("Scenario #%d:\n", c);
    if (success) {
      for (int i = 1; i <= p * q; ++i) printf("%c%c", path[i].y, path[i].x);
      printf("\n");
    } else printf("impossible\n");
    if (c != kase) printf("\n");
  }
  return 0;
}
