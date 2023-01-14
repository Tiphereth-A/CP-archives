#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
#define N 100005
ll t, a[N], b[N];
int main() {
  scanf("%lld", &t);
  while (t--) {
    ll m, n;
    scanf("%lld%lld", &n, &m);
    ll f = 0;
    _for(i, 1, n) {
      scanf("%lld", a + i);
      if (a[i] == 1) {
        --i;
        --n;
      } else if (a[i] == 0) {
        f = 1;
        break;
      }
    }
    _for(i, 1, m) {
      scanf("%lld", b + i);
      if (b[i] == 1) {
        --i;
        --m;
      } else if (b[i] == 0) {
        f = 1;
        break;
      }
    }
    if (f == 1 || n - m != 1 || n == 0) {
      printf("NO\n");
      continue;
    }
    std::sort(a + 1, a + n + 1, std::greater<ll>());
    std::sort(b + 1, b + m + 1, std::greater<ll>());
    ll p = 0;
    _for(i, 1, m)
      if (a[i] != b[i]) {
        p = a[i];
        break;
      }
    if (!p) p = a[n];
    ll sq = sqrt(p);
    _for(i, 2, sq)
      if (p % i == 0) {
        f = -1;
        break;
      }
    puts(f == -1 ? "NO" : "YES");
  }
  return 0;
}
