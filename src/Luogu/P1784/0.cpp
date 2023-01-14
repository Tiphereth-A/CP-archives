#include <bits/stdc++.h>
const int N = 10;
int g[N][N];
bool ln[N][N], col[N][N], zone[N][N];
int get_zone(int x, int y) { return ((x - 1) / 3) * 3 + ((y - 1) / 3) + 1; }
void print() {
  for (int i = 1; i <= 9; ++i) {
    for (int j = 1; j <= 9; ++j) printf("%d ", g[i][j]);
    putchar('\n');
  }
}
void dfs(int x = 1, int y = 1) {
  if (g[x][y]) {
    if (x == 9 && y == 9) print();
    (y == 9) ? dfs(x + 1, 1) : dfs(x, y + 1);
  } else {
    bool *tmp_ln = &ln[x][1], *tmp_col = &col[y][1],
         *tmp_zone = &zone[get_zone(x, y)][1];
    for (int i = 1, *tmp_g = &g[x][y]; i <= 9;
         ++i, ++tmp_ln, ++tmp_col, ++tmp_zone) {
      if (*tmp_ln || *tmp_col || *tmp_zone) continue;
      *tmp_ln = *tmp_col = *tmp_zone = *tmp_g = i;
      if (x == 9 && y == 9) print();
      (y == 9) ? dfs(x + 1, 1) : dfs(x, y + 1);
      *tmp_ln = *tmp_col = *tmp_zone = *tmp_g = 0;
    }
  }
}
int main() {
  for (int tmp, i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j) {
      scanf("%d", &tmp);
      ln[i][tmp] = col[j][tmp] = zone[get_zone(i, j)][g[i][j] = tmp] = true;
    }
  dfs();
  return 0;
}
