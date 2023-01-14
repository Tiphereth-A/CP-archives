#include <bits/stdc++.h>
using namespace std;
const int N = 101;
const int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1},
          dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int n, m;
char maps[N][N];
int ans;
void dfs(int x, int y) {
  maps[x][y] = '.';
  for (int i = 0; i < 8; ++i) {
    int xx = x + dx[i], yy = y + dy[i];
    if (xx <= 0 || xx > n || yy <= 0 || yy > m || maps[xx][yy] == '.') continue;
    dfs(xx, yy);
  }
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) cin >> maps[i][j];
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (maps[i][j] == 'W') {
        dfs(i, j);
        ++ans;
      }
  cout << ans;
}
