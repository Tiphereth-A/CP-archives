#include <bits/stdc++.h>
i64 a[3000005] = {0, 1}, n, p;
int main() {
  scanf("%lld%lld", &n, &p);
  for (int i = 2; i <= n; i++) a[i] = (p - p / i) * 1ll * a[p % i] % p;
  for (int i = 1; i <= n; i++) printf("%lld\n", a[i]);
  return 0;
}
