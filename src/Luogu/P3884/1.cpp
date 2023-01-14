#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y, y ^= x, x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
#define N 105
int dep[N], f[8][N], wid[N];
int n;
int ansd, answ;
int lca(int u, int v) {
  if (dep[u] > dep[v]) Swap(u, v);
  int dis = dep[v] - dep[u];
  _rfor(i, 7, 0)
    if ((1 << i) & dis) v = f[i][v];
  if (u == v) return u;
  _rfor(i, 7, 0)
    if (f[i][u] != f[i][v]) {
      u = f[i][u];
      v = f[i][v];
    }
  return f[0][u];
}
int main() {
  scanf("%d", &n);
  int tmp1, tmp2, tmpd;
  _for(i, 1, n - 1) {
    scanf("%d%d", &tmp1, &tmp2);
    f[0][tmp2] = tmp1;
    ansd = Max(ansd, tmpd = dep[tmp2] = dep[tmp1] + 1);
    answ = Max(answ, ++wid[tmpd]);
  }
  _for(i, 1, n)
    for (int j = 1; (1 << j) <= dep[i]; ++j) f[j][i] = f[j - 1][f[j - 1][i]];
  scanf("%d%d", &tmp1, &tmp2);
  int tmp3 = lca(tmp1, tmp2);
  printf(
    "%d\n%d\n%d\n", ansd + 1, answ, dep[tmp1] * 2 + dep[tmp2] - dep[tmp3] * 3);
  return 0;
}
