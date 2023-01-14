#include <bits/stdc++.h>
int a[355], b[5];
int f[41][41][41][41];
int max(int a, int b) { return a > b ? a : b; }
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  for (int i = 1; i <= m; ++i) {
    int tmp;
    scanf("%d", &tmp);
    ++b[tmp];
  }
  f[0][0][0][0] = a[1];
  int b1 = b[1], b2 = b[2], b3 = b[3], b4 = b[4];
  for (int i = 0; i <= b1; ++i)
    for (int j = 0; j <= b2; ++j)
      for (int k = 0; k <= b3; ++k)
        for (int l = 0; l <= b4; ++l) {
          int d = 1 + i + j * 2 + k * 3 + l * 4;
          int tmp = a[d];
          if (i) f[i][j][k][l] = max(f[i][j][k][l], f[i - 1][j][k][l] + tmp);
          if (j) f[i][j][k][l] = max(f[i][j][k][l], f[i][j - 1][k][l] + tmp);
          if (k) f[i][j][k][l] = max(f[i][j][k][l], f[i][j][k - 1][l] + tmp);
          if (l) f[i][j][k][l] = max(f[i][j][k][l], f[i][j][k][l - 1] + tmp);
        }
  printf("%d", f[b1][b2][b3][b4]);
  return 0;
}
