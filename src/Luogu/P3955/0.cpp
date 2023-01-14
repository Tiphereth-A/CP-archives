#include <bits/stdc++.h>
int n, q, a[1005] = {0};
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) scanf("%d", a + i);
  for (int i = 1; i <= q; i++) {
    int l, m, now = 1, min = 10000005;
    scanf("%d%d", &l, &m);
    for (int j = 1; j <= l; j++) now *= 10;
    for (int j = 1; j <= n; j++)
      if (((a[j] % now) == m) && (min > a[j])) min = a[j];
    if (min == 10000005) min = -1;
    printf("%d\n", min);
  }
  return 0;
}
