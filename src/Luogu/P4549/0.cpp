#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
A Gcd(const A &x, const A &y) {
  return y ? Gcd(y, x % y) : x;
}
template <typename A>
void read(A &x) {
  char c;
  A neg = 1;
  do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
  if (c == '-') neg = -1, c = getchar();
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c - 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
  x *= neg;
}
int n, m, s;
int main() {
  read(n);
  _for(i, 1, n) read(m), s = Gcd(s, Abs(m));
  printf("%d", s);
  return 0;
}
