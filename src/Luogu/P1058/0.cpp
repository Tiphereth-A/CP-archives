#include <bits/stdc++.h>
int m, n, lenx, leny, a[1005][1005], z[6] = {2, 1, 0, 0, 0, 0},
                                     s[6] = {6, 6, 6, 6, 5, 4};
char c[1005][1005], c1[10][10] = {
                      "  +---+",
                      " /   /|",
                      "+---+ |",
                      "|   | +",
                      "|   |/",
                      "+---+",
};
void cover(int x, int y) {
  for (int i = 5; i >= 0; --i)
    for (int j = z[i]; j <= s[i]; ++j) {
      c[5 - i + x][j + y] = c1[i][j];
      if (5 - i + x > lenx) lenx = 5 - i + x;
      if (j + y > leny) leny = j + y;
    }
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < m; ++j) scanf("%d", &a[i][j]);
  for (int o = 1; o <= n; ++o)
    for (int k = 0; k < m; ++k)
      for (int l = 0; l < a[o][k]; ++l)
        cover(((n - o) << 1) + 1 + 3 * l, ((n - o) << 1) + 1 + (k << 2));
  for (int i = lenx; i >= 1; --i) {
    for (int j = 1; j <= leny; ++j)
      if (c[i][j] == '\000') printf(".");
      else printf("%c", c[i][j]);
    printf("\n");
  }
}
