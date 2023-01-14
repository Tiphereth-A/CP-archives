#include <bits/stdc++.h>
typedef long long ll;
ll a[3000005], n, p;
void inv() {
  a[1] = 1;
  for (int i = 2; i <= n; i++) a[i] = (p - p / i) * 1ll * a[p % i] % p;
}
int main() {
  scanf("%lld%lld", &n, &p);
  inv();
  for (int i = 1; i <= n; i++) printf("%lld\n", a[i]);
  return 0;
}
