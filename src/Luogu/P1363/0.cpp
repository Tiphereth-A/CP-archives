#include <bits/stdc++.h>
#define mem(a) memset(a, 0, sizeof(a))
#define _for(i, l, r) for (int i(l); i < r; ++i)
#define N 1505
using namespace std;
char g[N][N];
bool m1[N * 2][N * 2], m2[N][N];
int n, m, nn, mm;
bool dfs(int x, int y) {
  if (x == -1) {
    if (dfs(nn - 1, y)) return true;
    return false;
  }
  if (x == nn) {
    if (dfs(0, y)) return true;
    return false;
  }
  if (y == -1) {
    if (dfs(x, mm - 1)) return true;
    return false;
  }
  if (y == mm) {
    if (dfs(x, 0)) return true;
    return false;
  }
  if (m1[x][y] || g[x % n][y % m] == '#') { return false; }
  if (m2[x % n][y % m]) { return true; }
  m1[x][y] = m2[x % n][y % m] = true;
  if (dfs(x + 1, y)) return true;
  if (dfs(x - 1, y)) return true;
  if (dfs(x, y + 1)) return true;
  if (dfs(x, y - 1)) return true;
  return false;
}
int main() {
  ios::sync_with_stdio(false);
  while (cin >> n >> m) {
    nn = n * 2;
    mm = m * 2;
    int xx, yy;
    _for(i, 0, n) {
      _for(j, 0, m) {
        cin >> g[i][j];
        if (g[i][j] == 'S') {
          xx = i;
          yy = j;
        }
      }
    }
    mem(m1);
    mem(m2);
    if (dfs(xx, yy)) cout << "Yes" << endl;
    else cout << "No" << endl;
  }
  return 0;
}
