#include <bits/stdc++.h>
using namespace std;
int f[60][60][60][60], g[60][60];
int main() {
  int n, m, x, y, z;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) cin >> g[i][j];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      for (int k = 1; k <= n; k++)
        for (int l = 1; l <= m; l++) {
          f[i][j][k][l] =
            max(max(f[i - 1][j][k][l - 1], f[i][j - 1][k - 1][l]),
                max(f[i - 1][j][k - 1][l], f[i][j - 1][k][l - 1])) +
            g[i][j] + g[k][l];
          if (i == k && l == j) f[i][j][k][l] -= g[i][j];
        }
  cout << f[n][m - 1][n - 1][m];
  return 0;
}
