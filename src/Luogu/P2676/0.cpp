#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
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
const int M = 200005;
int n, b, a[M], f[M], ans;
int main() {
  read(n, b);
  _for(i, 1, n) read(a[i]);
  std::sort(a + 1, a + n + 1, std::greater<int>());
  int cnt = 0;
  while (ans < b) ans += a[++cnt];
  printf("%d\n", cnt);
  return 0;
}
