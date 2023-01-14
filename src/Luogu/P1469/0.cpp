#include <bits/stdc++.h>
int ans, n;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int tmp;
    scanf("%d", &tmp);
    ans ^= tmp;
  }
  printf("%d", ans);
  return 0;
}
