#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
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
template <typename A, typename B>
void read(A &a, B &b) {
  read(a), read(b);
}
const int N = 205;
int n, m, a[N][N], f[N][N], MAXN;
int main() {
  read(n, m);
  int pos = (m >> 1) + 1;
  memset(a, 0xffffffff, sizeof(a));
  _for(i, 1, n)
    _for(j, 1, m) read(a[i][j]);
  _for(i, 1, n)
    _for(j, 1, m)
      f[i][j] =
        a[i][j] + Max(f[i - 1][j + 1], Max(f[i - 1][j], f[i - 1][j - 1]));
  MAXN = Max(Max(f[n][pos], f[n][pos - 1]), f[n][pos + 1]);
  printf("%d", MAXN);
  return 0;
}
