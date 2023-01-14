#include <bits/stdc++.h>
using namespace std;
const int dx[8] = {0, 0, 1, 1, -1, -1, 1, -1};
const int dy[8] = {1, -1, 1, -1, 1, -1, 0, 0};
int n, m;
vector<string> want, now;
bool vis[1005][1005];
void dfs(int x, int y) {
  bool flag = 0;
  for (int k = 0; k < 8; ++k) {
    int xx = x + dx[k], yy = y + dy[k];
    if (xx < 0 || xx >= n || yy < 0 || yy >= m || want[xx][yy] == '.') {
      flag = 1;
      break;
    }
  }
  for (int k = 0; k < 8; ++k) {
    int xx = x + dx[k], yy = y + dy[k];
    if (!flag) now[xx][yy] = '#';
    if (xx < 0 || xx >= n || yy < 0 || yy >= m || vis[xx][yy]) continue;
    vis[xx][yy] = true;
    dfs(xx, yy);
  }
}
int main() {
  cin >> n >> m;
  want.resize(n);
  now.resize(n, string(m, '.'));
  for (int i = 0; i < n; ++i) cin >> want[i];
  dfs(0, 0);
  for (int i = 0; i < n; ++i)
    if (want[i] != now[i]) {
      cout << "NO\n";
      return 0;
    }
  cout << "YES\n";
  return 0;
}
