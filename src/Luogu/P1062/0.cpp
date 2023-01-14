#include <bits/stdc++.h>
int k, n, i;
long long ans;
int main() {
  scanf("%d%d", &k, &n);
  while (n) {
    ans += (n & 1) * pow(k, i++);
    n >>= 1;
  }
  printf("%lld", ans);
  return 0;
}
