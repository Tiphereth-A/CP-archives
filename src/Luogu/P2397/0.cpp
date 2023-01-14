#include <bits/stdc++.h>
int cnt, ans, m, n;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &m);
    if (cnt == 0) {
      ans = m;
      cnt = 1;
    } else cnt += ((ans == m) ? 1 : -1);
  }
  printf("%d", ans);
  return 0;
}
