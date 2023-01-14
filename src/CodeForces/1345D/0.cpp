#include <bits/stdc++.h>
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _fd(i, r, l) for (auto i = (r); i >= (l); --i)
const int N = 1e3 + 5;
const int d[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
char _[N][N];
bool vis[N][N];
int n, m;
bool dfs(int x, int y) {
  if (vis[x][y] || _[x][y] == '.') return 0;
  vis[x][y] = 1;
  for (const int *i : d) {
    int now_x = x + *i, now_y = y + *(i + 1);
    if (now_x <= 0 || now_y <= 0 || now_x > n || now_y > m) continue;
    dfs(now_x, now_y);
  }
  return 1;
}
int main() {
  scanf("%d %d\n", &n, &m);
  _for(i, 1, n) {
    fgets(_[i] + 1, m + 1, stdin);
    if (_[i][1] == 10) fgets(_[i] + 1, m + 1, stdin);
  }
  int while_line = 0, while_col = 0;
  for (int i = 1, f; i <= n; ++i) {
    f = 1;
    _for(j, 1, m)
      if (_[i][j] == '#') f = 0;
    while_line += f;
  }
  for (int i = 1, f; i <= m; ++i) {
    f = 1;
    _for(j, 1, n)
      if (_[j][i] == '#') f = 0;
    while_col += f;
  }
  if ((while_line == 0) ^ (while_col == 0)) {
    puts("-1");
    return 0;
  }
  for (int i = 1, l, r; i <= n; ++i) {
    l = r = 0;
    _for(j, 1, m)
      if (_[i][j] == '#') {
        l = j;
        break;
      }
    _fd(j, m, 1) if (_[i][j] == '#') {
      r = j;
      break;
    }
    _for(j, l, r)
      if (_[i][j] == '.') {
        puts("-1");
        return 0;
      }
  }
  for (int i = 1, l, r; i <= m; ++i) {
    l = r = 0;
    _for(j, 1, n)
      if (_[j][i] == '#') {
        l = j;
        break;
      }
    _fd(j, n, 1) if (_[j][i] == '#') {
      r = j;
      break;
    }
    _for(j, l, r)
      if (_[j][i] == '.') {
        puts("-1");
        return 0;
      }
  }
  int cnt = 0;
  _for(i, 1, n)
    _for(j, 1, m) cnt += dfs(i, j);
  printf("%d\n", cnt);
  return 0;
}
