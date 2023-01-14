#include <bits/stdc++.h>
const int N = 55;
int f[N][N];
int main() {
  int t;
  for (int i = 0; i <= 50; i++)
    for (int j = 1; j <= 50; j++) {
      if (j == 1 || i == 0) f[i][j] = 1;
      else if (i < j) f[i][j] = f[i][i];
      else f[i][j] = f[i - j][j] + f[i][j - 1];
    }
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d\n", f[n][m]);
  }
  return 0;
}
