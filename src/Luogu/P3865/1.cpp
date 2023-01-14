#include <bits/stdc++.h>
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
void print() {}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  int f = 0;
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == '-') f = 1;
    ch = getc();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
  if (f) x = -x;
  read(oth...);
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <typename T, typename... T2>
void print(T x, T2... oth) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = hh;
  print(oth...);
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int M = 15 + 5;
const int N = 1e5 + 5;
int n, m, st[M][N];
int main() {
  read(n, m);
  _for(i, 1, n) read(st[0][i]);
  _for(i, 1, M - 1)
    _for(j, 1, N - (1 << i) + 1)
      st[i][j] = std::max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
  _for(i, 1, m) {
    int l, r;
    read(l, r);
    int k = 0;
    while (l + (1 << k) - 1 < r - (1 << k) + 1) ++k;
    print(std::max(st[k][l], st[k][r - (1 << k) + 1]));
  }
  FastIO::flush();
  return 0;
}
