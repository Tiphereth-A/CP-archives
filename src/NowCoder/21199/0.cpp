#include <bits/stdc++.h>
int main() {
  long long n, p;
  scanf("%lld%lld", &n, &p);
  long long ans = 0;
  for (int tmp = p, i = p; i <= n; tmp = (i += p)) {
    while (tmp && tmp % p == 0) {
      ++ans;
      tmp /= p;
    }
  }
  printf("%lld", ans);
  return 0;
}
