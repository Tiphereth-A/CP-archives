#include <bits/stdc++.h>
const int mod = 1e9 + 7;
long long qpow(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1) (res *= a) %= mod;
    (a *= a) %= mod;
    b >>= 1;
  }
  return res % mod;
}
int main() {
  long long w, n, k;
  scanf("%lld%lld%lld", &w, &n, &k);
  printf("%lld", w * qpow(qpow(2, k), mod - 2) % mod);
  return 0;
}
