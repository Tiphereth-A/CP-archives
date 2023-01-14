#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define Max(a, b) (((a) > (b)) ? (a) : (b))
#define MAXN 100005
int a[MAXN], st[MAXN][20], n, m;
int main() {
  scanf("%d%d", &n, &m);
  _for(i, 1, n) {
    scanf("%d", &a[i]);
    st[i][0] = a[i];
  }
  int r = (int)(log2((double)n));
  for (int j = 1; j <= r; j++)
    for (int i = 1; i + (1 << j) - 1 <= n; i++)
      st[i][j] = Max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
  while (m--) {
    int x, y;
    scanf("%d%d", &x, &y);
    r = (int)(log2(double(y - x + 1)));
    printf("%d\n", Max(st[x][r], st[y - (1 << r) + 1][r]));
  }
  return 0;
}
