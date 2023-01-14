#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define gi(a) do {
char ch;
while ((a = getchar()) > '9' || a < '0');
for (a -= '0'; (ch = getchar()) >= '0' && ch <= '9'; a = a * 10 + ch - '0');
}
while (0)
#define MAXN 100005
  int Max(int x, int y) {
    int m = (x - y) >> 31;
    return (y & m | x & ~m);
  }
int a[MAXN], st[MAXN][20], n, m;
int main() {
  gi(n);
  gi(m);
  _for(i, 1, n) {
    gi(a[i]);
    st[i][0] = a[i];
  }
  int r = (int)(log2((double)n));
  for (int j = 1; j <= r; j++)
    for (int i = 1; i + (1 << j) - 1 <= n; i++)
      st[i][j] = Max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
  while (m--) {
    int x, y;
    gi(x);
    gi(y);
    r = (int)(log2(double(y - x + 1)));
    printf("%d\n", Max(st[x][r], st[y - (1 << r) + 1][r]));
  }
  return 0;
}
