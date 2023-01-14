#include <bits/stdc++.h>
const int N = 8e4 + 5;
int n, opt, mod, min, max;
i64 b[N], s[N];
int l, r, k;
i64 now, ans;
char op[15];
int main() {
  scanf("%d%d%d%d%d", &n, &opt, &mod, &min, &max);
  for (int i = 1; i <= opt; ++i) {
    scanf("%s%d%d", op, &l, &r);
    if (*op == 'A') {
      scanf("%d", &k);
      b[l] += k;
      b[r + 1] -= k;
    } else {
      now = ans = 0;
      for (int j = 1; j < l; ++j) now += b[j];
      for (int j = l; j <= r; ++j) {
        now += b[j];
        i64 tmp = (now * j) % mod;
        if (tmp >= min && tmp <= max) ++ans;
      }
      printf("%lld\n", ans);
    }
  }
  scanf("%d", &k);
  now = 0;
  for (int i = 1; i <= n; ++i) {
    now += b[i];
    i64 tmp = (now * i) % mod;
    s[i] = (tmp >= min && tmp <= max) ? s[i - 1] + 1 : s[i - 1];
  }
  for (int i = 1; i <= k; ++i) {
    scanf("%d%d", &l, &r);
    printf("%lld\n", s[r] - s[l - 1]);
  }
  return 0;
}
