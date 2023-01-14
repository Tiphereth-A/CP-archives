#include <bits/stdc++.h>
const int N = 8e4 + 5;
i64 n, opt, mod, min, max;
i64 b[N], s[N];
i64 l, r, now, ans;
char op[15];
int main() {
  scanf("%lld%lld%lld%lld%lld", &n, &opt, &mod, &min, &max);
  for (i64 i = 1; i <= opt; ++i) {
    scanf("%s%lld%lld", op, &l, &r);
    if (*op == 'A') {
      scanf("%lld", &now);
      b[l] += now;
      b[r + 1] -= now;
    } else {
      now = ans = 0;
      for (i64 j = 1; j < l; ++j) now += b[j];
      for (i64 j = l; j <= r; ++j) {
        now += b[j];
        i64 tmp = (now * j) % mod;
        if (tmp >= min && tmp <= max) ++ans;
      }
      printf("%lld\n", ans);
    }
  }
  scanf("%lld", &ans);
  now = 0;
  for (i64 i = 1; i <= n; ++i) {
    now += b[i];
    i64 tmp = (now * i) % mod;
    s[i] = (tmp >= min && tmp <= max) ? s[i - 1] + 1 : s[i - 1];
  }
  for (i64 i = 1; i <= ans; ++i) {
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", s[r] - s[l - 1]);
  }
  return 0;
}
