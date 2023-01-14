#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2005;
typedef int MAT[N][N];
int m, n, k;
MAT mat, matlu, matld, matru, matrd;
int max(int a, int b) { return a > b ? a : b; }
int main() {
  int x;
  scanf("%d%d%d", &m, &n, &k);
  _for(i, 1, m)
    _for(j, 1, n) {
      scanf("%d", &x);
      mat[i][j] = mat[i][j - 1] + mat[i - 1][j] - mat[i - 1][j - 1] + x;
    }
  _rfor(i, m, k)
    _rfor(j, n, k)
      mat[i][j] -= mat[i - k][j] + mat[i][j - k] - mat[i - k][j - k];
  _for(i, k, m)
    _for(j, k, n)
      matlu[i][j] = max(max(matlu[i - 1][j], matlu[i][j - 1]), mat[i][j]);
  _for(i, k, m)
    _rfor(j, n, k)
      matru[i][j] = max(max(matru[i - 1][j], matru[i][j + 1]), mat[i][j]);
  _rfor(i, m, k)
    _for(j, k, n)
      matld[i][j] = max(max(matld[i + 1][j], matld[i][j - 1]), mat[i][j]);
  _rfor(i, m, k)
    _rfor(j, n, k)
      matrd[i][j] = max(max(matrd[i + 1][j], matrd[i][j + 1]), mat[i][j]);
  int MAXN = -1;
  _for(i, k, m - k)
    _for(j, k, n - k)
      MAXN = max(MAXN,
                 max(max(matlu[i][j] + matru[i][j + k] + matld[i + k][n],
                         matlu[i][n] + matld[i + k][j] + matrd[i + k][j + k]),
                     max(matrd[i + k][j + k] + matru[i][j + k] + matlu[i][j],
                         matlu[m][j] + matrd[i + k][j + k] + matru[i][j + k])));
  _for(i, k, m - k)
    _for(j, k * 2, n - k)
      MAXN = max(MAXN, matlu[m][j - k] + matru[m][j + k] + mat[i][j]);
  _for(i, k * 2, m - k)
    _for(j, k, n - k)
      MAXN = max(MAXN, matlu[i - k][n] + matld[i + k][n] + mat[i][j]);
  printf("%d", MAXN);
  return 0;
}
