#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = ' ';
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
template <typename T>
void print_h(T x, char h) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = h;
}
void putchar(char a) { buf2[++p3] = a; }
}  // namespace FastIO
#define read FastIO::read
#define print FastIO::print
#define print_h FastIO::print_h
const int N = 1e4 + 5;
int n, a[N], b[N], cnt;
int main() {
  read(n);
  _for(i, 1, n) read(a[i]);
  _rep(i, 1, n) if (Gcd(a[i], a[i + 1]) > 1) b[++cnt] = i;
  print_h(cnt, '\n');
  for (int i = 1, j = b[1], k = 1; i <= n; ++i) {
    print(a[i]);
    if (i == j) {
      print(1);
      j = b[++k];
    }
  }
  FastIO::flush();
  return 0;
}
