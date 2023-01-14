#include <bits/stdc++.h>
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
typedef double db;
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y ^= x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
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
void putchar(char a) { buf2[++p3] = a; }
}  // namespace FastIO
#define read FastIO::read
#define print FastIO::print
const int N = 1e4 + 5;
db a[N], b[N];
int main() {
  int n;
  read(n);
  _rfor(i, n - 1, 0) {
    a[i] = a[i + 1] + 1.0 * n / (n - i);
    b[i] = 1.0 * i * (2 * a[i] + 1) / (n - i) + b[i + 1] + 2 * a[i + 1] + 1;
  }
  printf("%.2lf", (a[0] + b[0]) / 2);
  FastIO::flush();
  return 0;
}
