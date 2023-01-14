#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
typedef long long i64;
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
int main() {
  int kase;
  read(kase);
  while (kase--) {
    i64 n, _, maxn;
    read(n);
    vector<i64> cnt(n + 1);
    _for(i, 1, n) {
      read(_);
      maxn = max(_, maxn);
      if (_ > n) continue;
      ++cnt[_];
    }
    if (maxn <= n) {
      print(n + 1);
      continue;
    }
    i64 ans = 1;
    _ = 0;
    _for(i, 1, n)
      if (cnt[i]) {
        _ += cnt[i];
        if (ans + _ > i) {
          ans += _;
          _ = 0;
        }
      }
    print(ans);
  __end_kase:;
  }
FINISHED:
  FastIO::flush();
  return 0;
}
