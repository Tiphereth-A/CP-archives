#include <bits/stdc++.h>
using namespace std;
using i128 = __int128_t;
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf;
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
void read() {}
template <class T>
void read(T &x) {
  int f = x = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == '-') f = 1;
    ch = getc();
  }
  while (isdigit(ch)) { x = x * 10 + ch - '0', ch = getc(); }
  if (f) x = -x;
}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  read(x);
  read(oth...);
}
void print() {}
void print(char a) { buf2[++p3] = a; }
template <class T>
void print(T x) {
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
}
template <typename T, typename... T2>
void print(T x, T2... oth) {
  if (p3 > 1 << 20) flush();
  print(x);
  print(oth...);
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
void solve() {
  i64 n, p;
  read(n, p);
  if (p == 1) {
    puts("0");
    return;
  }
  if (p > n) {
    printf("%lld\n", n);
    return;
  }
  i64 ans = n, _n = n;
  i128 _p = p;
  int f = -1;
  while (_n / _p) {
    ans += f * (_n / _p);
    _p *= p;
    f *= -1;
  }
  printf("%lld\n", ans);
}
int main() {
  int _t;
  read(_t);
  while (_t--) solve();
  return 0;
}
