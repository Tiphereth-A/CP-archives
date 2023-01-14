#include <bits/stdc++.h>
const int N = 1e4 + 5;
#define _for(i, a, b) for (int i = (a); i <= (b); ++i)
int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    (x *= 10) += c - '0';
    c = getchar();
  }
  return x * f;
}
bool map[N][N];
int n, m, ans = 0x3f3f3f3f;
int sx, sy, ex, ey;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
struct node {
  int x, y, dep;
};
std::queue<node> q;
void bfs() {
  while (!q.empty()) {
    node now = q.front();
    q.pop();
    int x = now.x, y = now.y, dep = now.dep;
    map[x][y] = 0;
    _for(i, 0, 3) {
      int xx = x + dx[i], yy = y + dy[i];
      if (xx < 1 || xx > 2 * n + 1 || yy < 1 || yy > 2 * m + 1 || !map[xx][yy])
        continue;
      xx += dx[i];
      yy += dy[i];
      if (xx < 1 || xx > 2 * n + 1 || yy < 1 || yy > 2 * m + 1 || !map[xx][yy])
        continue;
      if (xx == ex && yy == ey) {
        ans = now.dep + 1;
        return;
      }
      q.push({xx, yy, dep + 1});
      yy[xx[map]] = 0;
    }
  }
}
int main() {
  n = read();
  m = read();
  char c;
  _for(i, 1, n * 2 + 1)
    _for(j, 1, m * 2 + 2) {
      c = getchar();
      if (c != '+' && c != '-' && c != '|' && c != '\n') j[i[map]] = 1;
      if (c == 's') {
        sx = i;
        sy = j;
        j[i[map]] = 0;
      }
      if (c == 'e') {
        ex = i;
        ey = j;
      }
    }
  q.push({sx, sy, 0});
  bfs();
  printf("%d", ans);
  return 0;
}
