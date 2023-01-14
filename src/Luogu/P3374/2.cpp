#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _lowbit(x) (1 << __builtin_ctz(x))
const int N = 5e5 + 5;
i64 a[N];
int m, n;
void add(int pos, i64 x) {
  for (int i = pos; i <= n; i += _lowbit(i)) a[i] += x;
}
i64 query(int pos) {
  i64 ans = 0;
  for (int i = pos; i; i -= _lowbit(i)) ans += a[i];
  return ans;
}
int main() {
  scanf("%d%d", &n, &m);
  i64 tmp;
  _for(i, 1, n) {
    scanf("%lld", &tmp);
    add(i, tmp);
  }
  for (int i = 1, o, x, y; i <= m; ++i) {
    scanf("%d%d%d", &o, &x, &y);
    if (o & 1) add(x, y);
    else printf("%lld\n", query(y) - query(x - 1));
  }
  return 0;
}
