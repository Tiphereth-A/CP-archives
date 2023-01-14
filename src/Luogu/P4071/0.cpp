#include <bits/stdc++.h>
const int N = 1e6 + 5, MOD = 1e9 + 7;
i64 frac[N] = {1}, inv[N], d[N];
i64 qpow(i64 a, i64 b = MOD - 2, i64 mod = MOD) {
  i64 res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  d[2] = 1;
  for (int i = 1; i < N; ++i) frac[i] = frac[i - 1] * i % MOD;
  for (int i = 1; i < N; ++i) inv[i] = qpow(frac[i]);
  for (int i = 3; i < N; ++i) d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % MOD;
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    i64 n, m;
    scanf("%lld%lld", &n, &m);
    if (m == n) puts("1");
    else if (n - m == 1) puts("0");
    else if (m == 0) printf("%lld\n", d[n]);
    else
      printf("%lld\n",
             frac[n] * inv[m] % MOD * inv[n - m] % MOD * d[n - m] % MOD);
  }
  return 0;
}
