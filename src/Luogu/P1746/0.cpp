#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
struct node {
  int x, y, step;
  bool operator==(const node &other) const {
    return x == other.x && y == other.y;
  }
} start, end;
int n, map[1005][1005];
std::queue<node> queue;
bool valid(int x, int y) {
  return x > 0 && y > 0 && x <= n && y <= n && !map[x][y];
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) scanf("%1d", &map[i][j]);
  scanf("%d%d%d%d", &start.x, &start.y, &end.x, &end.y);
  queue.push(start);
  while (!queue.empty()) {
    node now = queue.front();
    queue.pop();
    if (now == end) {
      printf("%d", now.step);
      break;
    }
    for (int i = 0; i < 4; ++i) {
      int xx = now.x + dx[i], yy = now.y + dy[i];
      if (valid(xx, yy)) {
        map[xx][yy] = 1;
        queue.push({xx, yy, now.step + 1});
      }
    }
  }
  return 0;
}
