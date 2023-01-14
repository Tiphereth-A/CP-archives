#include <bits/stdc++.h>
char map[12][12];
const int dx[4]{-1, 0, 1, 0}, dy[4]{0, 1, 0, -1};
int vis[11][11][11][11];
struct Node {
  int x, y, dir;
  friend bool operator!=(Node const &a, Node const &b) {
    return a.x != b.x || a.y != b.y;
  }
  friend void operator++(Node &a) {
    if (int nx = a.x + dx[a.dir], ny = a.y + dy[a.dir]; map[nx][ny] != '*')
      a.x = nx, a.y = ny;
    else ++a.dir %= 4;
  }
};
int main() {
  Node jhon, cow;
  std::fill(map[0], map[0] + 12, '*');
  std::fill(map[11], map[11] + 12, '*');
  for (int i = 1; i <= 10; ++i) {
    scanf("%s\n", &map[i][1]);
    map[i][0] = map[i][11] = '*';
    for (int j = 1; j <= 10; ++j) {
      if (map[i][j] == 'C') cow = {i, j, 0};
      if (map[i][j] == 'F') jhon = {i, j, 0};
    }
  }
  int ans = 0;
  while (jhon != cow) {
    if (vis[jhon.x][jhon.y][cow.x][cow.y]++ == 4) {
      std::cout << "0\n";
      return 0;
    }
    ++ans, ++jhon, ++cow;
  }
  std::cout << ans << '\n';
  return 0;
}
