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
int lis(int f, int l) {
  int g[N] = {0};
  int len = 1;
  if (f < l) {
    g[1] = a[f];
    _for(i, f, l) {
      if (a[i] > g[len]) g[++len] = a[i];
      else {
        int j = std::lower_bound(g + 1, g + len + 1, a[i]) - g;
        g[j] = a[i];
      }
    }
  } else if (f > l) {
    g[1] = a[l];
    _rfor(i, f, l) {
      if (a[i] > g[len]) g[++len] = a[i];
      else {
        int j = std::lower_bound(g + 1, g + len + 1, a[i]) - g;
        g[j] = a[i];
      }
    }
  }
  return len;
}
int main() {
  read(n);
  _for(i, 1, n) read(a[i]);
  _for(i, 1, n) {
    f[i] = lis(1, i) + lis(n, i) - 1;
    MAXN = Max(MAXN, f[i]);
  }
  printf("%d", n - MAXN);
  return 0;
}
