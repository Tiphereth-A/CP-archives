#include <bits/stdc++.h>
#define _rep(i, l, r) for (auto i = (l); i < (r); ++i)
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
using FastIO::print;
using FastIO::print_h;
using FastIO::read;
const int N = 4000 + 5;
int n, m;
struct line {
  i64 cost;
  bool is_ln;
  bool operator<(const line &other) const { return cost > other.cost; }
} a[N];
int main() {
  read(n, m);
  _rep(i, 1, n) {
    read(a[i].cost);
    a[i].is_ln = 1;
  }
  _rep(i, n, m + n - 1) {
    read(a[i].cost);
    a[i].is_ln = 0;
  }
  std::sort(a + 1, a + m + n - 1);
  i64 ans = 0, coeff_ln = 1, coeff_col = 1;
  _rep(i, 1, m + n - 1) {
    if (a[i].is_ln) {
      ans += a[i].cost * coeff_ln;
      ++coeff_col;
    } else {
      ans += a[i].cost * coeff_col;
      ++coeff_ln;
    }
  }
  print(ans);
ex:
  FastIO::flush();
  return 0;
}
