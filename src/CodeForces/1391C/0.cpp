#include <bits/stdc++.h>
const int MOD = 1e9 + 7;
long long qpow(long long a, long long b, long long mod = MOD) {
  long long res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  int n;
  scanf("%d", &n);
  long long ans = 1;
  for (int i = 1; i <= n; ++i) (ans *= i) %= MOD;
  (((ans -= qpow(2, n - 1)) %= MOD) += MOD) %= MOD;
  printf("%lld\n", ans);
  return 0;
}
