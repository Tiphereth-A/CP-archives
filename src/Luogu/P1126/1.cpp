#include <bits/stdc++.h>
using namespace std;
struct point {
  int x, y;
  bool operator==(const point &other) const {
    return x == other.x && y == other.y;
  }
};
struct node {
  point p;
  int step, dir;
};
point delta[4][3] = {{{0, 1}, {0, 2}, {0, 3}},
                     {{1, 0}, {2, 0}, {3, 0}},
                     {{0, -1}, {0, -2}, {0, -3}},
                     {{-1, 0}, {-2, 0}, {-3, 0}}};
int maps[155][155];
point start_point, end_point;
char dir;
queue<node> q;
int main() {
  int n, m;
  cin >> n >> m;
  for (int __m, i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      cin >> __m;
      if (__m)
        maps[i][j] = maps[i][j + 1] = maps[i + 1][j] = maps[i + 1][j + 1] = -1;
    }
  cin >> start_point.x >> start_point.y >> end_point.x >> end_point.y >> dir;
  if (start_point == end_point) {
    cout << 0;
    return 0;
  }
  q.push({start_point,
          0,
          ((dir == 'E') ? 0 : ((dir == 'S') ? 1 : ((dir == 'W') ? 2 : 3)))});
  maps[start_point.x][start_point.y] = 0;
  while (!q.empty()) {
    node now = q.front();
    q.pop();
    if (now.p == end_point) continue;
    for (int dir = 0; dir < 4; ++dir)
      for (int i = 0; i < 3; ++i) {
        int xx = now.p.x + delta[dir][i].x, yy = now.p.y + delta[dir][i].y;
        if (xx > 0 && xx < n && yy > 0 && yy < m) {
          if (maps[xx][yy] == -1) break;
          int tmp_step =
            now.step +
            std::min(4 - std::abs(dir - now.dir), std::abs(dir - now.dir)) + 1;
          if (maps[xx][yy] == 0 || maps[xx][yy] >= tmp_step) {
            maps[xx][yy] = tmp_step;
            q.push({{xx, yy}, tmp_step, dir});
          }
        }
      }
  }
  cout << (maps[end_point.x][end_point.y] > 0 ? maps[end_point.x][end_point.y] :
                                                -1);
}
