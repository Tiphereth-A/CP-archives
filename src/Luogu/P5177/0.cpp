#include <bits/stdc++.h>
const u64 mod = 1e9 + 7;
u64 f(u64 n) {
  n %= mod;
  return (n + 1) * n / 2 % mod;
}
u64 a[64];
int main() {
  for (int i = 1; i < 64; ++i) a[i] = (f((1ull << i - 1) - 1) + a[i - 1]) % mod;
  int t;
  scanf("%d", &t);
  while (t--) {
    u64 n;
    scanf("%llu", &n);
    printf(
      "%llu\n",
      (a[63 - __builtin_clzll(n)] + f(n - (1ull << 63 - __builtin_clzll(n)))) *
        2 % mod);
  }
}
