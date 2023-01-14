#include <bits/stdc++.h>
using namespace std;
const int diff[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e3 + 5;
struct node {
  int x, y, step;
  bool operator==(const node &other) const {
    return x == other.x && y == other.y;
  }
} start, ended;
queue<node> q;
int maps[N][N];
int n;
bool valid(int x, int y) {
  return x > 0 && y > 0 && x <= n && y <= n && !maps[x][y];
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) scanf("%1d", &maps[i][j]);
  cin >> start.x >> start.y >> ended.x >> ended.y;
  q.push(start);
  while (!q.empty()) {
    node now = q.front();
    q.pop();
    if (now == ended) {
      cout << now.step;
      break;
    }
    for (auto i : diff) {
      int xx = now.x + i[0], yy = now.y + i[1];
      if (valid(xx, yy)) {
        maps[xx][yy] = 1;
        q.push({xx, yy, now.step + 1});
      }
    }
  }
}
