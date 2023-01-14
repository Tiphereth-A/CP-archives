#include <bits/stdc++.h>
const int MOD = 1e9 + 7;
long long qpow(long long a, long long b, long long mod = MOD) {
  long long res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  long long n;
  scanf("%lld", &n);
  long long _ = qpow(2, (n - 1) % (MOD - 1));
  n %= MOD;
  printf("%lld", (n + (_ + 1) * (((_ * 2 - n - 1) % MOD + MOD) % MOD)) % MOD);
  return 0;
}
