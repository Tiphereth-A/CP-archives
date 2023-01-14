#include <bits/stdc++.h>
#define re int
long long n, ans, f[100010];
int main() {
  scanf("%lld", &n);
  for (re i = n; i; --i) {
    f[i] = n / i * (n / i);
    for (re j = i << 1; j <= n; j += i) f[i] -= f[j];
    ans += f[i] * i;
  }
  printf("%lld", ans);
  return 0;
}
