#include <bits/stdc++.h>
#define ctn continue
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
const int N = 205;
int n, m, a[N][N], f[N][N], ans;
int main() {
  scanf("%d%d", &n, &m);
  _for(i, 1, n)
    _for(j, 1, m) scanf("%d", &a[i][j]);
  _for(i, 1, n)
    _for(j, 1, m) {
      if (a[i][j] == 0) ctn;
      f[i][j] = Min(Min(f[i - 1][j], f[i][j - 1]), f[i - 1][j - 1]) + 1;
    }
  _for(i, 1, n)
    _for(j, 1, m) ans = Max(ans, f[i][j]);
  printf("%d\n", ans);
  return 0;
}
