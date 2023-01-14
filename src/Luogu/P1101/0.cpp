#include <bits/stdc++.h>
#define MAXN 105
char f[MAXN][MAXN];
bool flag[MAXN][MAXN];
char c[6] = {'i', 'z', 'h', 'o', 'n', 'g'};
int d[8][2] = {
  {1, 0}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, -1}, {-1, 0}};
int n, dx, dy;
using namespace std;
void r(int x, int y, int step, int dir) {
  if (step >= 7) return;
  flag[x][y] = true;
  dx = x + d[dir][0];
  dy = y + d[dir][1];
  r(dx, dy, step + 1, dir);
}
void dfs(int x, int y, int step, int dir) {
  if (x < 0 || y < 0 || x > n || y > n) return;
  if (step == 6) {
    r(x, y, 0, 7 - dir);
    return;
  }
  dx = x + d[dir][0];
  dy = y + d[dir][1];
  if (f[dx][dy] != c[step]) return;
  else dfs(dx, dy, step + 1, dir);
}
int main() {
  cin >> n;
  int x, y;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < n; j++) cin >> f[i][j];
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < n; j++) {
      if (f[i][j] == 'y') {
        for (int k = 0; k <= 7; k++) dfs(i, j, 0, k);
      }
    }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < n; j++)
      if (flag[i][j]) cout << f[i][j];
      else cout << '*';
    cout << endl;
  }
  return 0;
}
