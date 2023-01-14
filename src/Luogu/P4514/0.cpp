#include <bits/stdc++.h>
#define lowbit(x) (1 << __builtin_ctz(x))
char op;
int m, n;
struct BIT {
  int tree[2051][2051];
  void update(int x, int y, int k) {
    for (int i = x; i <= n; i += lowbit(i))
      for (int j = y; j <= m; j += lowbit(j)) tree[i][j] += k;
  }
  int query(int x, int y) {
    int ans = 0;
    for (int i = x; i; i -= lowbit(i))
      for (int j = y; j; j -= lowbit(j)) ans += tree[i][j];
    return ans;
  }
} d, di, dj, dij;
void add(int x, int y, int k) {
  d.update(x, y, k);
  di.update(x, y, k * x);
  dj.update(x, y, k * y);
  dij.update(x, y, k * x * y);
}
int ans(int x, int y) {
  return d.query(x, y) * (x * y + x + y + 1) - di.query(x, y) * (y + 1) -
         dj.query(x, y) * (x + 1) + dij.query(x, y);
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
