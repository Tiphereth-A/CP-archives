#include <bits/stdc++.h>
#define abs(x) (x < 0 ? -(x) : (x))
#define max(x, y) (x > y ? x : y)
int n, x, y;
int main() {
  scanf("%d%d%d", &n, &x, &y);
  int p = max(abs(n - (x << 1) + 1), abs(n - (y << 1) + 1)) + 1;
  if (x > y) printf("%d\n", (n - p) * (n + p + 1) + (p << 2) - x - y - 1);
  else printf("%d\n", (n - p) * (n + p - 1) + x + y - 1);
  return 0;
}
