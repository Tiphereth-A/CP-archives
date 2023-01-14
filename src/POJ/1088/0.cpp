#include <algorithm>
#include <cstdio>
#include <cstring>
using std::max;
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int len[105][105], a[105][105];
int m, n;
int f(int x, int y) {
  int ans = 0;
  if (len[x][y]) return len[x][y];
  for (int tx, ty, k = 0; k <= 3; ++k) {
    tx = dir[k][0] + x;
    ty = dir[k][1] + y;
    if (tx < 0 || ty < 0 || tx > m - 1 || ty > n - 1) continue;
    if (a[tx][ty] < a[x][y]) ans = max(ans, f(tx, ty));
  }
  return len[x][y] = ans + 1;
}
int main() {
  while (~scanf("%d%d", &m, &n)) {
    memset(a, 0, sizeof(a));
    memset(len, 0, sizeof(len));
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j) scanf("%d", &a[i][j]);
    int ans = -1;
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j) ans = max(ans, f(i, j));
    printf("%d\n", ans);
  }
  return 0;
}
