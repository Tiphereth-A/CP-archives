#include <bits/stdc++.h>
#define N 100005
long long t, a[N], b[N], m, n, f, p;
int main() {
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld%lld", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
      if (a[i] == 1) {
        --i;
        --n;
      }
    }
    for (int i = 0; i < m; ++i) {
      scanf("%lld", &b[i]);
      if (b[i] == 1) {
        --i;
        --m;
      }
    }
    if (n - m != 1 || !n) {
      puts("NO");
      continue;
    }
    std::sort(a, a + n);
    std::sort(b, b + m);
    for (int i = m; i ^ -1; --i)
      if (a[i] != b[i]) {
        p = a[i];
        break;
      }
    if (!p) p = a[m];
    for (int i = 2, sq = sqrt(p); i <= sq; ++i)
      if (p % i == 0) {
        f = -1;
        break;
      }
    puts(~f ? "YES" : "NO");
  }
  return 0;
}
