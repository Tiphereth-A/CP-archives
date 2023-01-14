#include <bits/stdc++.h>
int g[10][10];
bool ln[10][10], col[10][10], zon[10][10];
int getz(int x, int y) { return ((x - 1) / 3) * 3 + ((y - 1) / 3) + 1; }
void print() {
  for (int i = 1; i <= 9; ++i) {
    for (int j = 1; j <= 9; ++j) printf("%d ", g[i][j]);
    putchar('\n');
  }
}
void dfs(int x, int y) {
  if (g[x][y]) {
    if (x == 9 && y == 9) print();
    (y == 9) ? dfs(x + 1, 1) : dfs(x, y + 1);
  } else {
    int *tmpg = &g[x][y];
    bool *tmpln = &ln[x][1], *tmpcol = &col[y][1], *tmpz = &zon[getz(x, y)][1];
    for (int i = 1; i <= 9; ++i, ++tmpln, ++tmpcol, ++tmpz) {
      if (*tmpln || *tmpcol || *tmpz) continue;
      *tmpg = i;
      *tmpln = *tmpcol = *tmpz = true;
      if (x == 9 && y == 9) print();
      (y == 9) ? dfs(x + 1, 1) : dfs(x, y + 1);
      *tmpg = 0;
      *tmpln = *tmpcol = *tmpz = false;
    }
  }
}
int main() {
  int tmp;
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j) {
      scanf("%d", &tmp);
      g[i][j] = tmp;
      ln[i][tmp] = col[j][tmp] = zon[getz(i, j)][tmp] = true;
    }
  dfs(1, 1);
  return 0;
}
