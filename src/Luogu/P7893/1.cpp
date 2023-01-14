#include <bits/stdc++.h>
using namespace std;
namespace FastIO {
char buf[1 << 21], *p1 = buf, *p2 = buf;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
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
}  // namespace FastIO
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
  i64 ans = n, _n = n / p;
  int f = -1;
  while (_n) {
    ans += f * _n;
    _n /= p;
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
