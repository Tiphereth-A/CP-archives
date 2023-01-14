#include <bits/stdc++.h>
int main() {
  long long n, p, k;
  scanf("%lld%lld%lld", &n, &p, &k);
  printf("%lld", ((p % n) * (k % n)) % n);
  return 0;
}
