#include <bits/stdc++.h>
int n, a[100005];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  long long max = a[1], ans = a[1], now = a[1];
  for (int i = 2; i <= n; ++i) {
    if (a[i] < now) now = a[i];
    else {
      ans += a[i] - now;
      max = now = a[i];
    }
  }
  printf("%lld", ans);
  return 0;
}
