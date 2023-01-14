#include <bits/stdc++.h>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    unsigned long long l, r;
    scanf("%llu%llu", &l, &r);
    unsigned long long len = (r - l + 1) % 9, ans = 0;
    for (int i = 1, m = l % 9; i <= len; ++i, ++m) ans += m;
    printf("%llu\n", ans % 9);
  }
}
