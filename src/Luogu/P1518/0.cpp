#include <bits/stdc++.h>
using namespace std;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
struct Node {
  int x, y, face;
  friend void operator++(Node &a) {
    int nx = a.x + dx[a.face];
    int ny = a.y + dy[a.face];
    if (g[nx][ny] != '*') {
      a.x = nx;
      a.y = ny;
    } else (++a.face) %= 4;
  }
  friend bool operator!=(const Node &a, const Node &b) {
    return a.x != b.x || a.y != b.y;
  }
};
char g[12][12];
int vis[11][11][11][11];
int main() {
  Node jhon, cow;
  fill(g[0], g[0] + 12, '*');
  fill(g[11], g[11] + 12, '*');
  for (int i = 1; i <= 10; i++) {
    scanf("%s\n", &g[i][1]);
    g[i][0] = g[i][11] = '*';
    for (int j = 1; j <= 10; j++) {
      if (g[i][j] == 'C') cow = (Node){i, j, 0};
      if (g[i][j] == 'F') jhon = (Node){i, j, 0};
    }
  }
  int ans = 0;
  while (jhon != cow) {
    if (vis[jhon.x][jhon.y][cow.x][cow.y]++ == 4) {
      printf("0");
      return 0;
    }
    ++ans;
    ++jhon;
    ++cow;
  }
  printf("%d\n", ans);
  return 0;
}
