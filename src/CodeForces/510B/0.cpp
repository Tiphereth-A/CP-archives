#include <bits/stdc++.h>
using namespace std;
const int dx[]{0, 0, 1, -1};
const int dy[]{-1, 1, 0, 0};
int n, m, flag;
int cnt[31];
vector<string> mp;
bool vis[55][55];
bool check(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= m) return 0;
  return 1;
}
void dfs(int x, int y, int fx, int fy) {
  char ch = mp[x][y];
  vis[x][y] = 1;
  for (int i = 0; i < 4; ++i) {
    int xx = x + dx[i];
    int yy = y + dy[i];
    if (xx == fx && yy == fy) continue;
    if (!check(xx, yy) || mp[xx][yy] != ch) continue;
    if (vis[xx][yy]) flag = 1;
    else dfs(xx, yy, x, y);
  }
  return;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m;
  mp.resize(n);
  for (int i = 0; i < n; ++i) cin >> mp[i];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) cnt[mp[i][j] - 'A']++;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (!vis[i][j] && cnt[mp[i][j] - 'A'] >= 4) dfs(i, j, -1, -1);
      if (flag) {
        cout << "Yes\n";
        return 0;
      }
    }
  if (!flag) cout << "No\n";
  return 0;
}
