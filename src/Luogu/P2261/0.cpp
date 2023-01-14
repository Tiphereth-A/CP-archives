#include <bits/stdc++.h>
u64 min(u64 a, u64 b) { return a < b ? a : b; }
int main() {
  u64 n, k;
  scanf("%llu%llu", &n, &k);
  u64 ans = n * k;
  for (u64 i = 1, r, tmp; i <= n; i = r + 1) {
    r = (tmp = k / i) ? min(k / tmp, n) : n;
    ans -= tmp * (r - i + 1) * (i + r) >> 1;
  }
  printf("%llu", ans);
  return 0;
}
