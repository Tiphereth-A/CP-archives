#include <bits/stdc++.h>
int a[17];
int main() {
  int n, i;
  scanf("%d", &n);
  for (i = 1; i <= n; i++) scanf("%d", &a[i]);
  std::sort(a + 1, a + n + 1);
  for (i = 1; i <= n; i++) printf("%d ", a[i]);
  return 0;
}
