#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 105;
const int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1},
          dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int n, m;
char map[N][N];
void dfs(int x, int y) {
  map[x][y] = '.';
  for (int i = 0; i < 8; ++i) {
    int xx = x + dx[i], yy = y + dy[i];
    if (xx <= 0 || xx > n || yy <= 0 || yy > m || map[xx][yy] == '.') continue;
    dfs(xx, yy);
  }
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) cin >> map[i][j];
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      if (map[i][j] == 'W') {
        dfs(i, j);
        ++ans;
      }
    }
  cout << ans;
  return 0;
}
