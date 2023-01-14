#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define M 105
const int MOD = 1000007;
int n, m, f[M][M];
int main() {
  scanf("%d%d", &n, &m);
  _for(i, 0, n) f[i][0] = 1;
  _for(i, 1, n) {
    int a;
    scanf("%d", &a);
    _for(j, 0, a)
      _for(k, 0, m - j) {
        if (j == 0 && k == 0) continue;
        f[i][j + k] = (f[i][j + k] + f[i - 1][k]) % MOD;
      }
  }
  printf("%d\n", f[n][m] % MOD);
  return 0;
}
