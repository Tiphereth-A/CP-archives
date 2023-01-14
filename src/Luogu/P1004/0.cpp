#include <bits/stdc++.h>
using namespace std;
int f[10][10][10][10], g[10][10];
int main() {
  int n, x, y, m;
  cin >> n;
  do {
    cin >> x >> y >> m;
    g[x][y] = m;
  } while (x != 0 || y != 0 || m != 0);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= n; k++)
        for (int l = 1; l <= n; l++) {
          f[i][j][k][l] =
            max(max(f[i - 1][j][k - 1][l], f[i][j - 1][k - 1][l]),
                max(f[i - 1][j][k][l - 1], f[i][j - 1][k][l - 1])) +
            g[i][j] + g[k][l];
          if (i == k && l == j) f[i][j][k][l] -= g[i][j];
        }
  cout << f[n][n][n][n];
  return 0;
}
