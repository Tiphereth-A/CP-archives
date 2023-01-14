#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
void read(A &x) {
  char c;
  A neg = 1;
  do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
  if (c == '-') neg = -1, c = getchar();
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
  x *= neg;
}
const int N = 105;
int n, a[N], f[N], g[N], MAXN;
int main() {
  read(n);
  _for(i, 1, n) read(a[i]);
  _for(i, 1, n)
    _for(j, 0, i - 1)
      if (a[i] > a[j]) f[i] = Max(f[i], f[j] + 1);
  _rfor(i, n, 1)
    _rfor(j, n + 1, i + 1)
      if (a[i] > a[j]) g[i] = Max(g[i], g[j] + 1);
  _for(i, 1, n) MAXN = Max(MAXN, f[i] + g[i] - 1);
  printf("%d", n - MAXN);
  return 0;
}
