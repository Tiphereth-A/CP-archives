#include <bits/stdc++.h>
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, ch;
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
template <typename T>
void read(T &x) {
  x = 0;
  while (ch = getc(), !isdigit(ch));
  while (isdigit(ch)) {
    (x *= 10) += ch - 48;
    ch = getc();
  }
}
template <typename T1, typename T2>
void read(T1 &x, T2 &y) {
  read(x);
  read(y);
}
template <typename T>
void print(T x) {
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = '\n';
  fwrite(buf2, 1, p3 + 1, stdout), p3 = -1;
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int _N = 2e5 + 5;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rrep(i, l) for (int i = (l); i; --i)
int a[_N << 2], t[_N << 2];
int n, N = 1, m;
int max(int a, int b) {
  int m = (b - a) >> 31;
  return a & m | b & ~m;
}
void build() {
  _for(i, 1, n) t[N + i] = a[i];
  _rrep(i, N - 1) t[i] = max(t[i << 1], t[i << 1 | 1]);
}
void modify(int x, int k) {
  for (int i = N + x; i; i >>= 1) t[i] = max(t[i], k);
}
int query(int x, int y) {
  int ans = 0;
  for (int s = N + x - 1, r = N + y + 1; s ^ r ^ 1; s >>= 1, r >>= 1) {
    if (~s & 1) ans = max(ans, t[s ^ 1]);
    if (r & 1) ans = max(ans, t[r ^ 1]);
  }
  return ans;
}
char c;
int x, y;
int main() {
  read(n, m);
  while (N < n + 2) N <<= 1;
  _for(i, 1, n) read(a[i]);
  build();
  while (m--) {
    FastIO::getc();
    c = FastIO::getc();
    read(x, y);
    if (c == 'Q') print(query(x, y));
    else modify(x, y);
  }
  return 0;
}
