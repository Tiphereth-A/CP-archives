#include <bits/stdc++.h>
const int N = 2e5 + 5;
i64 a[N], ans;
int n, q, s, t;
i64 get(i64 num) { return num > 0 ? -num * s : -num * t; }
int main() {
  int pre;
  scanf("%d%d%d%d%d", &n, &q, &s, &t, &pre);
  for (int i = 1; i <= n; ++i) {
    int tmp;
    scanf("%d", &tmp);
    ans += get(a[i] = tmp - pre);
    pre = tmp;
  }
  int l, r, x;
  for (int i = 1; i <= q; ++i) {
    scanf("%d%d%d", &l, &r, &x);
    ans -= get(a[l]);
    ans += get(a[l] += x);
    if (r != n) {
      ans -= get(a[r + 1]);
      ans += get(a[r + 1] -= x);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
