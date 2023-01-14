#include <bits/stdc++.h>
int main() {
  int m, n, max = -1;
  scanf("%d%d", &n, &m);
  for (int x, y, i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    if (x) y = n - y;
    if (y > max) max = y;
  }
  printf("%d", max);
  return 0;
}
