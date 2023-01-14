#include <bits/stdc++.h>
long long t, n, k;
int main() {
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld%lld", &n, &k);
    ((n & k) == k) ? printf("1\n") : printf("0\n");
  }
  return 0;
}
