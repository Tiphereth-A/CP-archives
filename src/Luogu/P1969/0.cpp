#include <bits/stdc++.h>
int n, s1, s0, ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &s1);
    if (s1 > s0) ans += s1 - s0;
    s0 = s1;
  }
  printf("%d", ans);
  return 0;
}
