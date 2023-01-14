#include <bits/stdc++.h>
bool f[105][105];
int n, m, t, sx, sy, fx, fy;
int sum;
using namespace std;
void dfs(int m, int n) {
  if (m == fx && n == fy) {
    sum++;
    return;
  } else {
    f[m][n] = false;
    if (f[m - 1][n]) {
      dfs(m - 1, n);
      f[m - 1][n] = true;
    }
    if (f[m][n - 1]) {
      dfs(m, n - 1);
      f[m][n - 1] = true;
    }
    if (f[m + 1][n]) {
      dfs(m + 1, n);
      f[m + 1][n] = true;
    }
    if (f[m][n + 1]) {
      dfs(m, n + 1);
      f[m][n + 1] = true;
    }
  }
}
int main() {
  cin >> n >> m >> t >> sx >> sy >> fx >> fy;
  int x, y;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) f[i][j] = true;
  for (int i = 1; i <= t; i++) {
    cin >> x >> y;
    f[x][y] = false;
  }
  dfs(sx, sy);
  cout << sum;
  return 0;
}
