#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
#define N 200005
ll a[N], b[N];
int t, m, n, p, pre = 2;
ll lucas(int x, int y) {
  if (x < y) return 0;
  return (x < p) ? (b[x] * a[y] * a[x - y] % p) :
                   (lucas(x / p, y / p) * lucas(x % p, y % p) % p);
}
int main() {
  scanf("%d", &t);
  a[0] = a[1] = b[1] = b[0] = 1LL;
  while (t--) {
    scanf("%d%d%d", &n, &m, &p);
    _for(i, 2, n + m) {
      b[i] = b[i - 1] * i % p;
      a[i] = (p - p / i) * a[p % i] % p;
    }
    _for(i, 2, n + m) a[i] = a[i - 1] * a[i] % p;
    printf("%lld\n", lucas(n + m, n));
  }
  return 0;
}
