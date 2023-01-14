#include <bits/stdc++.h>
using namespace std;
#define _rfor(i, r, l, vals...) \
  for (decltype(r - l) i = (r), ##vals; i >= (l); --i)
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
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) { ch = getc(); }
  while (isdigit(ch)) { x = x * 10 + ch - '0', ch = getc(); }
}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  read(x);
  read(oth...);
}
}  // namespace FastIO
using FastIO::read;
void solve() {
  int n, m;
  read(n, m);
  int a, b;
  _rfor(i, int(ceil(sqrt(n))), 1)
    if (n % i == 0) {
      a = i;
      b = n / i;
      break;
    }
  puts((a + b) * 2 + 4 <= m ? "Good" : "Miss");
}
int main() {
  int _t;
  read(_t);
  while (_t--) solve();
  return 0;
}
