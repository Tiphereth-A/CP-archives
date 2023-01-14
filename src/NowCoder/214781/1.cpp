#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
const int MOD = 998244353, inv2 = (MOD + 1) / 2;
i64 calc(i64 l, i64 r) {
  if (r < l) return 0;
  l %= MOD;
  r %= MOD;
  return (i128)(l + r) * (r - l + 1) % MOD * inv2 % MOD;
}
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    i64 m, n, x, y, k;
    scanf("%lld%lld%lld%lld%lld", &n, &m, &x, &y, &k);
    if (m > n) {
      swap(m, n);
      swap(x, y);
    }
    if (m == 1) {
      i64 l = min(x - 1, n - x), L = max(x - 1, n - x);
      if (k <= L + 1) {
        printf("%lld\n", calc(1, k));
        continue;
      }
      i64 t1 = max(0ll, min(l, (k - L) / 2));
      i64 t2 = max(k - 2 * t1 - L, (k > L) * ((k - L) & 1));
      i64 ans1 = calc(1, t1);
      i64 ans2 = (t1 * t2 % MOD + 2 * calc(1, t1 - 1) % MOD) % MOD;
      i64 ans3 = calc(2 * t1 + t2, k);
      printf("%lld\n", (ans1 + ans2 + ans3) % MOD);
      continue;
    }
    printf("%lld\n", calc(max(0ll, k - m * n) + 1, k));
  }
  return 0;
}
