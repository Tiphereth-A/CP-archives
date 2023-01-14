#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
struct point {
  int x, y;
  bool operator==(const point &other) const {
    return x == other.x && y == other.y;
  }
};
struct node {
  point p;
  int step;
  int dir;
};
point delta[4][3] = {{{0, 1}, {0, 2}, {0, 3}},
                     {{1, 0}, {2, 0}, {3, 0}},
                     {{0, -1}, {0, -2}, {0, -3}},
                     {{-1, 0}, {-2, 0}, {-3, 0}}};
int n, m;
int map[155][155];
point start, end;
char dir;
std::queue<node> queue;
int main() {
  cin >> n >> m;
  for (int __m, i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      cin >> __m;
      if (__m)
        map[i][j] = map[i][j + 1] = map[i + 1][j] = map[i + 1][j + 1] = -1;
    }
  cin >> start.x >> start.y >> end.x >> end.y >> dir;
  if (start == end) {
    cout << 0;
    return 0;
  }
  queue.push(
    {start,
     0,
     ((dir == 'E') ? 0 : ((dir == 'S') ? 1 : ((dir == 'W') ? 2 : 3)))});
  map[start.x][start.y] = 0;
  while (!queue.empty()) {
    node now = queue.front();
    queue.pop();
    if (now.p == end) { continue; }
    for (int dir = 0; dir < 4; ++dir)
      for (int i = 0; i < 3; ++i) {
        int xx = now.p.x + delta[dir][i].x, yy = now.p.y + delta[dir][i].y;
        if (xx > 0 && xx < n && yy > 0 && yy < m) {
          if (map[xx][yy] == -1) break;
          int tmp_step =
            now.step +
            std::min(4 - std::abs(dir - now.dir), std::abs(dir - now.dir)) + 1;
          if (map[xx][yy] == 0 || map[xx][yy] >= tmp_step) {
            map[xx][yy] = tmp_step;
            queue.push({{xx, yy}, tmp_step, dir});
          }
        }
      }
  }
  cout << (map[end.x][end.y] > 0 ? map[end.x][end.y] : -1);
  return 0;
}
