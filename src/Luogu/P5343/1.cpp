#include <bits/stdc++.h>
const int md = 1e9 + 7;
typedef long long LL;
int b[105];
void upd(int &a) { a += a >> 31 & md; }
struct mat {
  int a[100][100];
  void operator*=(const mat &b) {
    int c[100][100];
    memset(c, 0, sizeof c);
    for (int i = 0; i < 100; ++i)
      for (int j = 0; j < 100; ++j) {
        int &tmp = c[i][j];
        for (int k = 0; k < 100; k += 4)
          tmp =
            (tmp + (LL)a[i][k] * b.a[k][j] + (LL)a[i][k + 1] * b.a[k + 1][j] +
             (LL)a[i][k + 2] * b.a[k + 2][j] +
             (LL)a[i][k + 3] * b.a[k + 3][j]) %
            md;
      }
    memcpy(a, c, sizeof a);
  }
} a, c;
LL n;
int na, nb, dp[105];
void pow(mat a, LL b, mat &ret) {
  for (; b; b >>= 1, a *= a)
    if (b & 1) ret *= a;
}
int main() {
  scanf("%lld%d", &n, &na);
  for (int x; na--;) {
    scanf("%d", &x);
    b[x] = 1;
  }
  scanf("%d", &nb);
  for (int x; nb--;) {
    scanf("%d", &x);
    if (b[x]) a.a[100 - x][99] = 1;
  }
  for (int i = 1; i < 100; ++i) a.a[i][i - 1] = 1;
  dp[0] = 1;
  for (int i = 1; i <= 100; ++i)
    for (int j = 1; j <= i; ++j)
      if (a.a[100 - j][99]) upd(dp[i] += dp[i - j] - md);
  for (int i = 0; i < 100; ++i) c.a[0][i] = dp[i];
  pow(a, n, c);
  printf("%d\n", c.a[0][0]);
  return 0;
}
