#include <bits/stdc++.h>
#define lowbit(x) (1 << __builtin_ctz(x))
char op;
int m, n;
int tree[2051][2051][4];
void add(int x, int y, int k) {
  int kx = k * x, ky = k * y, kxy = k * x * y;
  for (int i = x; i <= n; i += lowbit(i))
    for (int j = y; j <= m; j += lowbit(j)) {
      tree[i][j][0] += k;
      tree[i][j][1] += kx;
      tree[i][j][2] += ky;
      tree[i][j][3] += kxy;
    }
}
int ans(int x, int y) {
  int ans = 0, len = x * y + x + y + 1, leny = x + 1, lenx = y + 1;
  for (int i = x; i; i -= lowbit(i))
    for (int j = y; j; j -= lowbit(j))
      ans += tree[i][j][0] * len - tree[i][j][1] * lenx - tree[i][j][2] * leny +
             tree[i][j][3];
  return ans;
}
int main() {
  int x1, x2, y1, y2, k;
  scanf("X %d %d\n", &n, &m);
  while (scanf("%c %d %d %d %d", &op, &x1, &y1, &x2, &y2) == 5) {
    if (op == 'L') {
      scanf("%d\n", &k);
      add(x1, y1, k);
      add(x1, y2 + 1, -k);
      add(x2 + 1, y1, -k);
      add(x2 + 1, y2 + 1, k);
    } else {
      scanf("\n");
      printf("%d\n",
             ans(x2, y2) - ans(x1 - 1, y2) - ans(x2, y1 - 1) +
               ans(x1 - 1, y1 - 1));
    }
  }
  return 0;
}
